# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/margin_trading/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = margin_trading::MarginTradingRestApi::production(std::move(cfg));

    using namespace margin_trading::rest_api;
    const auto response = client.cross_margin_collateral_ratio();
    std::cout << common::to_json(response.data()) << "\n";
}
```
