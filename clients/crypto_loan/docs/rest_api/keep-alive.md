# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/crypto_loan/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = crypto_loan::CryptoLoanRestApi::production(std::move(cfg));

    using namespace crypto_loan::rest_api;
    const GetFlexibleLoanAssetsDataParams params{};
    const auto response = client.get_flexible_loan_assets_data(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
