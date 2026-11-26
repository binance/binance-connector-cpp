//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

namespace binance::test {

struct PkeyDeleter {
    void operator()(EVP_PKEY* key) const noexcept { EVP_PKEY_free(key); }
};
using Pkey = std::unique_ptr<EVP_PKEY, PkeyDeleter>;

inline Pkey generate_rsa(unsigned bits = 2048) {
    return Pkey(EVP_PKEY_Q_keygen(nullptr, nullptr, "RSA", static_cast<size_t>(bits)));
}

inline Pkey generate_ed25519() {
    return Pkey(EVP_PKEY_Q_keygen(nullptr, nullptr, "ED25519"));
}

inline Pkey generate_ec_p256() {
    return Pkey(EVP_PKEY_Q_keygen(nullptr, nullptr, "EC", "P-256"));
}

inline std::string bio_to_string(BIO* bio) {
    char* data = nullptr;
    const long len = BIO_get_mem_data(bio, &data);
    std::string out(data, static_cast<std::size_t>(len));
    BIO_free(bio);
    return out;
}

/// PKCS#8 PEM, optionally encrypted with AES-256-CBC.
inline std::string private_pem(const Pkey& key, const char* passphrase = nullptr) {
    BIO* bio = BIO_new(BIO_s_mem());
    const EVP_CIPHER* cipher = passphrase != nullptr ? EVP_aes_256_cbc() : nullptr;
    if (PEM_write_bio_PKCS8PrivateKey(
            bio, key.get(), cipher, passphrase,
            passphrase != nullptr ? static_cast<int>(std::char_traits<char>::length(passphrase))
                                  : 0,
            nullptr, nullptr) != 1) {
        BIO_free(bio);
        throw std::runtime_error("PEM_write_bio_PKCS8PrivateKey failed");
    }
    return bio_to_string(bio);
}

inline std::string base64_decode(std::string_view in) {
    std::string out(3 * in.size() / 4 + 3, '\0');
    const int n = EVP_DecodeBlock(reinterpret_cast<unsigned char*>(out.data()),
                                  reinterpret_cast<const unsigned char*>(in.data()),
                                  static_cast<int>(in.size()));
    if (n < 0) {
        throw std::runtime_error("invalid base64");
    }
    std::size_t len = static_cast<std::size_t>(n);
    // EVP_DecodeBlock counts padding bytes as output.
    for (auto it = in.rbegin(); it != in.rend() && *it == '='; ++it) {
        --len;
    }
    out.resize(len);
    return out;
}

/// Verifies a base64 signature produced by `SignatureGenerator` with the key's public half.
inline bool verify(const Pkey& key, std::string_view payload, std::string_view signature_b64) {
    const auto sig = base64_decode(signature_b64);
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_PKEY_get_base_id(key.get()) == EVP_PKEY_ED25519 ? nullptr : EVP_sha256();
    bool ok = EVP_DigestVerifyInit(ctx, nullptr, md, nullptr, key.get()) == 1 &&
              EVP_DigestVerify(ctx, reinterpret_cast<const unsigned char*>(sig.data()), sig.size(),
                               reinterpret_cast<const unsigned char*>(payload.data()),
                               payload.size()) == 1;
    EVP_MD_CTX_free(ctx);
    return ok;
}

} // namespace binance::test
