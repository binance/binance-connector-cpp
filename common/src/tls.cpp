//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include "tls.hpp"

// Windows headers first: OpenSSL's own headers undefine the wincrypt macros that clash with its
// names (X509_NAME, ...), but only when they come later.
#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <memory>
#include <wincrypt.h>
#include <windows.h>
#else
#include <array>
#include <sys/stat.h>
#endif

#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/x509.h>

namespace binance::common::detail {

namespace {

// A client destroyed from its own callback finishes shutting down on a detached thread. OpenSSL's
// exit-time cleanup must not tear down the locks that thread may still use.
[[maybe_unused]] const bool kOpenSslNoAtExit =
    OPENSSL_init_crypto(OPENSSL_INIT_NO_ATEXIT, nullptr) == 1;

#if defined(_WIN32)
struct CertStoreCloser {
    void operator()(HCERTSTORE store) const noexcept { CertCloseStore(store, 0); }
};
struct CertContextFreer {
    void operator()(PCCERT_CONTEXT cert) const noexcept { CertFreeCertificateContext(cert); }
};
struct X509Deleter {
    void operator()(X509* x509) const noexcept { X509_free(x509); }
};
using CertStorePtr = std::unique_ptr<void, CertStoreCloser>;
using CertContextPtr = std::unique_ptr<const CERT_CONTEXT, CertContextFreer>;
using X509Ptr = std::unique_ptr<X509, X509Deleter>;
#endif

} // namespace

void load_system_root_certificates(SSL_CTX* ctx) {
    SSL_CTX_set_default_verify_paths(ctx);

#if defined(_WIN32)
    const CertStorePtr store(CertOpenSystemStoreW(0, L"ROOT"));
    if (store != nullptr) {
        X509_STORE* x509_store = SSL_CTX_get_cert_store(ctx);
        // CertEnumCertificatesInStore frees the context it is given, so the guard gives it up
        // before each call and only releases a context that the loop leaves early.
        for (CertContextPtr cert(CertEnumCertificatesInStore(store.get(), nullptr));
             cert != nullptr;
             cert.reset(CertEnumCertificatesInStore(store.get(), cert.release()))) {
            const unsigned char* der = cert->pbCertEncoded;
            const X509Ptr x509(d2i_X509(nullptr, &der, static_cast<long>(cert->cbCertEncoded)));
            if (x509 != nullptr) {
                X509_STORE_add_cert(x509_store, x509.get());
            }
        }
    }
#else
    constexpr std::array kBundles = {
        "/etc/ssl/cert.pem",                                 // macOS, Alpine, BSDs
        "/etc/ssl/certs/ca-certificates.crt",                // Debian, Ubuntu, Arch
        "/etc/pki/tls/certs/ca-bundle.crt",                  // RHEL, Fedora
        "/etc/pki/ca-trust/extracted/pem/tls-ca-bundle.pem", // RHEL 7+
        "/etc/ssl/ca-bundle.pem",                            // openSUSE
    };
    for (const char* path : kBundles) {
        struct stat st{};
        if (::stat(path, &st) == 0 && SSL_CTX_load_verify_locations(ctx, path, nullptr) == 1) {
            break;
        }
    }
#endif
    // Missing default paths leave errors on the queue; they must not leak into later calls.
    ERR_clear_error();
}

} // namespace binance::common::detail
