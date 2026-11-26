# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

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
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = crypto_loan::CryptoLoanRestApi::production(std::move(cfg));

    using namespace crypto_loan::rest_api;
    const GetFlexibleLoanAssetsDataParams params{};
    const auto response = client.get_flexible_loan_assets_data(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
