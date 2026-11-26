//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <vector>

#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/signer.hpp>

#include "utils.hpp"

namespace binance::common {

namespace {

struct PkeyDeleter {
    void operator()(EVP_PKEY* p) const noexcept { EVP_PKEY_free(p); }
};
struct MdCtxDeleter {
    void operator()(EVP_MD_CTX* p) const noexcept { EVP_MD_CTX_free(p); }
};
struct BioDeleter {
    void operator()(BIO* p) const noexcept { BIO_free(p); }
};
using PkeyPtr = std::unique_ptr<EVP_PKEY, PkeyDeleter>;

std::string openssl_error() {
    std::string out;
    while (const auto err = ERR_get_error()) {
        std::array<char, 256> buf{};
        ERR_error_string_n(err, buf.data(), buf.size());
        if (!out.empty()) {
            out += "; ";
        }
        out += buf.data();
    }
    return out;
}

[[noreturn]] void fail(const std::string& what) {
    const auto detail = openssl_error();
    throw ConnectorClientError(detail.empty() ? what : what + ": " + detail);
}

std::string to_hex(const unsigned char* data, std::size_t len) {
    constexpr std::string_view kHex = "0123456789abcdef";
    std::string out;
    out.reserve(len * 2);
    for (std::size_t i = 0; i < len; ++i) {
        out += kHex[data[i] >> 4U];
        out += kHex[data[i] & 0x0FU];
    }
    return out;
}

std::string to_base64(const std::vector<unsigned char>& data) {
    std::string out(4 * ((data.size() + 2) / 3), '\0');
    const int n = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(out.data()), data.data(),
                                  static_cast<int>(data.size()));
    out.resize(static_cast<std::size_t>(n));
    return out;
}

// Never prompt on the terminal for a passphrase. OpenSSL only asks for one when the key is
// encrypted, which `asked` records.
int no_passphrase(char* /*buf*/, int /*size*/, int /*rwflag*/, void* asked) {
    *static_cast<bool*>(asked) = true;
    return 0;
}

// Strips leading and trailing whitespace from every line, in place (no copy of the key), so that
// indented PEM text, e.g. from an indented string literal, parses.
void trim_lines(std::string& pem) {
    const auto is_space = [](char c) { return c == ' ' || c == '\t' || c == '\r'; };
    std::size_t out = 0;
    std::size_t i = 0;
    while (i < pem.size()) {
        auto end = pem.find('\n', i);
        const bool has_newline = end != std::string::npos;
        if (!has_newline) {
            end = pem.size();
        }
        auto first = i;
        auto last = end;
        while (first < last && is_space(pem[first])) {
            ++first;
        }
        while (last > first && is_space(pem[last - 1])) {
            --last;
        }
        for (auto k = first; k < last; ++k) {
            pem[out++] = pem[k];
        }
        if (has_newline) {
            pem[out++] = '\n';
        }
        i = end + 1;
    }
    OPENSSL_cleanse(pem.data() + out, pem.size() - out);
    pem.resize(out);
}

} // namespace

struct SignatureGenerator::Impl {
    std::optional<std::string> api_secret;
    std::optional<PrivateKey> private_key;
    mutable std::optional<std::string> passphrase; // wiped once the key is parsed

    mutable std::mutex mutex;
    mutable PkeyPtr key;

    [[nodiscard]] std::string raw_key_data() const {
        if (!private_key->is_file()) {
            return private_key->value();
        }
        const auto& path = private_key->value();
        std::error_code ec;
        if (!std::filesystem::exists(path, ec)) {
            throw ConnectorClientError("Private key file does not exist: " + path);
        }
        std::ifstream in(path, std::ios::binary | std::ios::ate);
        if (!in) {
            throw ConnectorClientError("Failed to read private key file: " + path);
        }
        // Read straight into one buffer (no stream copies) so it can be wiped afterwards.
        std::string pem(static_cast<std::size_t>(std::max<std::streamoff>(in.tellg(), 0)), '\0');
        in.seekg(0);
        if (!in.read(pem.data(), static_cast<std::streamsize>(pem.size()))) {
            OPENSSL_cleanse(pem.data(), pem.size());
            throw ConnectorClientError("Failed to read private key file: " + path);
        }
        return pem;
    }

    EVP_PKEY* key_object() const {
        std::lock_guard lock(mutex);
        if (key) {
            return key.get();
        }
        auto pem = raw_key_data();
        struct Wipe {
            std::string& s;
            ~Wipe() { OPENSSL_cleanse(s.data(), s.size()); }
        } wipe{pem};
        trim_lines(pem);
        std::unique_ptr<BIO, BioDeleter> bio(
            BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size())));
        if (!bio) {
            fail("Failed to parse private key");
        }
        ERR_clear_error();
        EVP_PKEY* parsed = nullptr;
        if (passphrase) {
            parsed = PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr,
                                             const_cast<char*>(passphrase->c_str()));
            if (parsed == nullptr) {
                fail("Failed to parse private key with passphrase");
            }
        } else {
            bool asked = false;
            parsed = PEM_read_bio_PrivateKey(bio.get(), nullptr, no_passphrase, &asked);
            if (parsed == nullptr) {
                if (asked) {
                    ERR_clear_error();
                    throw ConnectorClientError(
                        "Failed to parse private key: private key is encrypted; set "
                        "private_key_passphrase");
                }
                fail("Failed to parse private key");
            }
        }
        key.reset(parsed);
        if (passphrase) {
            OPENSSL_cleanse(passphrase->data(), passphrase->size());
            passphrase.reset();
        }
        return key.get();
    }
};

SignatureGenerator::SignatureGenerator(std::optional<std::string> api_secret,
                                       std::optional<PrivateKey> private_key,
                                       std::optional<std::string> private_key_passphrase)
    : impl_(std::make_unique<Impl>()) {
    impl_->api_secret = std::move(api_secret);
    impl_->private_key = std::move(private_key);
    impl_->passphrase = std::move(private_key_passphrase);
}

SignatureGenerator::~SignatureGenerator() = default;
SignatureGenerator::SignatureGenerator(SignatureGenerator&&) noexcept = default;
SignatureGenerator& SignatureGenerator::operator=(SignatureGenerator&&) noexcept = default;

std::string SignatureGenerator::sign(const Params& query, const Params* body) const {
    auto payload = detail::build_query_string(query);
    if (body != nullptr && !body->empty()) {
        payload += detail::build_query_string(*body);
    }
    return sign_payload(payload);
}

std::string SignatureGenerator::sign_unencoded(const Params& params) const {
    return sign_payload(detail::build_plain_query_string(params));
}

void SignatureGenerator::load_key() const {
    if (!impl_) {
        throw ConnectorClientError("SignatureGenerator was moved from");
    }
    if (impl_->private_key) {
        (void)impl_->key_object();
    }
}

std::string SignatureGenerator::sign_payload(std::string_view payload) const {
    if (!impl_) {
        throw ConnectorClientError("SignatureGenerator was moved from");
    }
    if (!impl_->private_key) {
        if (!impl_->api_secret) {
            throw ConnectorClientError(
                "Either 'api_secret' or 'private_key' must be provided for signed requests.");
        }
        const auto& secret = *impl_->api_secret;
        std::array<unsigned char, EVP_MAX_MD_SIZE> mac{};
        unsigned int mac_len = 0;
        if (HMAC(EVP_sha256(), secret.data(), static_cast<int>(secret.size()),
                 reinterpret_cast<const unsigned char*>(payload.data()), payload.size(), mac.data(),
                 &mac_len) == nullptr) {
            fail("HMAC signing failed");
        }
        return to_hex(mac.data(), mac_len);
    }

    EVP_PKEY* key = impl_->key_object();
    const int type = EVP_PKEY_get_base_id(key);
    const EVP_MD* md = nullptr;
    if (type == EVP_PKEY_RSA) {
        md = EVP_sha256();
    } else if (type != EVP_PKEY_ED25519) {
        const char* name = EVP_PKEY_get0_type_name(key);
        throw ConnectorClientError(std::string("Unsupported private key type: ") +
                                   (name != nullptr ? name : "unknown") +
                                   ". Must be RSA or ED25519.");
    }

    std::unique_ptr<EVP_MD_CTX, MdCtxDeleter> ctx(EVP_MD_CTX_new());
    if (!ctx || EVP_DigestSignInit(ctx.get(), nullptr, md, nullptr, key) != 1) {
        fail("Failed to create signer");
    }
    const auto* data = reinterpret_cast<const unsigned char*>(payload.data());
    std::size_t sig_len = 0;
    if (EVP_DigestSign(ctx.get(), nullptr, &sig_len, data, payload.size()) != 1) {
        fail("Signing failed");
    }
    std::vector<unsigned char> sig(sig_len);
    if (EVP_DigestSign(ctx.get(), sig.data(), &sig_len, data, payload.size()) != 1) {
        fail("Signing failed");
    }
    sig.resize(sig_len);
    return to_base64(sig);
}

} // namespace binance::common
