# Certificate Pinning

Pins the public key of the server certificate on top of the usual chain and host name checks, through the `agent` hook. Remember to update the pin before Binance rotates its certificate.

```cpp
#include <array>
#include <iostream>
#include <utility>

#include <boost/asio/ssl.hpp>
#include <openssl/evp.h>
#include <openssl/x509.h>

#include <binance/common/json.hpp>
#include <binance/dual_investment/rest_api.hpp>

using namespace binance;

// SHA-256 of the public key (DER SubjectPublicKeyInfo) of the certificate to pin, e.g. from
// openssl x509 -pubkey -noout -in cert.pem | openssl pkey -pubin -outform der | openssl dgst -sha256
constexpr std::array<unsigned char, 32> kPinnedKey{/* 32 bytes */};

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.agent = [](boost::asio::ssl::context& ctx) {
        ctx.set_verify_callback([](bool preverified, boost::asio::ssl::verify_context& vc) {
            X509_STORE_CTX* store = vc.native_handle();
            // `preverified` includes the chain and host name checks: keep them, and pin the server
            // certificate (depth 0) on top.
            if (!preverified || X509_STORE_CTX_get_error_depth(store) != 0) {
                return preverified;
            }
            std::array<unsigned char, 32> digest{};
            unsigned int size = 0;
            X509_pubkey_digest(X509_STORE_CTX_get_current_cert(store), EVP_sha256(), digest.data(),
                               &size);
            return size == digest.size() && digest == kPinnedKey;
        });
    };
    const auto client = dual_investment::DualInvestmentRestApi::production(std::move(cfg));

    using namespace dual_investment::rest_api;
    const GetDualInvestmentProductListParams params{
        .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
        .exercised_coin = "USDT",
        .invest_coin = "BNB"};
    const auto response = client.get_dual_investment_product_list(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
