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

#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl/context.hpp>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include "support/keys.hpp"

namespace binance::test {

/// A self-signed P-256 certificate, by default for `DNS:localhost` and `IP:127.0.0.1`. Each one
/// is generated once per test process.
struct TestCertificate {
    std::string cert_pem;
    std::string key_pem;

    static const TestCertificate& get() {
        static const TestCertificate instance = make("DNS:localhost,IP:127.0.0.1");
        return instance;
    }

    /// A certificate that is valid, but only for `example.com`.
    static const TestCertificate& for_other_host() {
        static const TestCertificate instance = make("DNS:example.com");
        return instance;
    }

    /// A certificate with a different subject, for CAs that must not interfere with the others
    /// (self-signed certificates with equal subjects shadow each other in a trust store).
    static const TestCertificate& unrelated() {
        static const TestCertificate instance = make("DNS:unrelated.example", "unrelated");
        return instance;
    }

    /// A server context presenting this certificate.
    [[nodiscard]] std::shared_ptr<boost::asio::ssl::context> server_context() const {
        auto ctx =
            std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_server);
        ctx->use_certificate_chain(boost::asio::buffer(cert_pem));
        ctx->use_private_key(boost::asio::buffer(key_pem), boost::asio::ssl::context::pem);
        return ctx;
    }

    /// Adds this certificate to a client context's trust store (use as `cfg.agent`).
    void trust(boost::asio::ssl::context& ctx) const {
        ctx.add_certificate_authority(boost::asio::buffer(cert_pem));
    }

private:
    static TestCertificate make(const char* subject_alt_names,
                                const char* common_name = "localhost") {
        const auto key = generate_ec_p256();
        std::unique_ptr<X509, decltype(&X509_free)> cert(X509_new(), X509_free);
        X509_set_version(cert.get(), 2);
        ASN1_INTEGER_set(X509_get_serialNumber(cert.get()), 1);
        X509_gmtime_adj(X509_getm_notBefore(cert.get()), -3600);
        X509_gmtime_adj(X509_getm_notAfter(cert.get()), 24L * 3600);
        X509_set_pubkey(cert.get(), key.get());
        X509_NAME* name = X509_get_subject_name(cert.get());
        X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC,
                                   reinterpret_cast<const unsigned char*>(common_name), -1, -1, 0);
        X509_set_issuer_name(cert.get(), name);

        X509V3_CTX v3{};
        X509V3_set_ctx_nodb(&v3);
        X509V3_set_ctx(&v3, cert.get(), cert.get(), nullptr, nullptr, 0);
        for (const auto& [nid, value] : {std::pair{NID_subject_alt_name, subject_alt_names},
                                         std::pair{NID_basic_constraints, "critical,CA:TRUE"}}) {
            X509_EXTENSION* ext = X509V3_EXT_conf_nid(nullptr, &v3, nid, value);
            if (ext == nullptr) {
                throw std::runtime_error("X509V3_EXT_conf_nid failed");
            }
            X509_add_ext(cert.get(), ext, -1);
            X509_EXTENSION_free(ext);
        }
        if (X509_sign(cert.get(), key.get(), EVP_sha256()) == 0) {
            throw std::runtime_error("X509_sign failed");
        }

        BIO* bio = BIO_new(BIO_s_mem());
        PEM_write_bio_X509(bio, cert.get());
        return {bio_to_string(bio), private_pem(key)};
    }
};

} // namespace binance::test
