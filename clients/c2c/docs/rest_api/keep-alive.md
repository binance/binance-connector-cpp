# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

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
    cfg.keep_alive = false;
    const auto client = c2c::C2CRestApi::production(std::move(cfg));

    using namespace c2c::rest_api;
    const GetC2CTradeHistoryParams params{};
    const auto response = client.get_c2c_trade_history(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
