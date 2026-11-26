# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/c2c/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = c2c::C2CRestApi::production(std::move(cfg));

    using namespace c2c::rest_api;
    const GetC2CTradeHistoryParams params{};
    const auto response = client.get_c2c_trade_history(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
