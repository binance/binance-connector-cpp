//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>

#include <binance/common/config.hpp>
#include <binance/common/export.hpp>
#include <binance/common/models.hpp>

namespace binance::common {

/// Signs request payloads.
///
/// - No private key → HMAC-SHA256 with `api_secret`, hex encoded.
/// - RSA private key → RSASSA-PKCS1-v1_5 with SHA-256, base64 encoded.
/// - Ed25519 private key → Ed25519, base64 encoded.
///
/// The key is read and parsed on first use (or by `load_key`) and then cached. The PEM text read
/// from a file and the passphrase are wiped from memory once parsed. Thread-safe.
/// Errors throw `ConnectorClientError`.
class BINANCE_COMMON_EXPORT SignatureGenerator {
public:
    SignatureGenerator(std::optional<std::string> api_secret, std::optional<PrivateKey> private_key,
                       std::optional<std::string> private_key_passphrase);
    ~SignatureGenerator();
    SignatureGenerator(SignatureGenerator&&) noexcept;
    SignatureGenerator& operator=(SignatureGenerator&&) noexcept;
    SignatureGenerator(const SignatureGenerator&) = delete;
    SignatureGenerator& operator=(const SignatureGenerator&) = delete;

    /// REST: signs `build_query_string(query) + build_query_string(body)`.
    [[nodiscard]] std::string sign(const Params& query, const Params* body = nullptr) const;

    /// WebSocket API: signs `build_plain_query_string(params)` (sorted, not percent-encoded).
    [[nodiscard]] std::string sign_unencoded(const Params& params) const;

    [[nodiscard]] std::string sign_payload(std::string_view payload) const;

    /// Reads and parses the private key now instead of on the first signature. It does nothing
    /// without a key and throws like `sign_payload`. `RestClient` calls it on construction, so a
    /// bad key fails early, not on the first order.
    void load_key() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace binance::common
