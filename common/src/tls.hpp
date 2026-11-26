//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <openssl/ssl.h>

namespace binance::common::detail {

/// Adds the operating system's trusted root CAs to `ctx`, on top of OpenSSL's defaults
/// (`SSL_CERT_FILE` / `SSL_CERT_DIR`). It reads the Windows ROOT store on Windows and the
/// well-known CA bundle files elsewhere. A vcpkg-built OpenSSL otherwise has an empty
/// trust store.
void load_system_root_certificates(SSL_CTX* ctx);

} // namespace binance::common::detail
