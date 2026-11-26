# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/copy_trading/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = copy_trading::CopyTradingRestApi::production(std::move(cfg));

    using namespace copy_trading::rest_api;
    const GetFuturesLeadTradingSymbolWhitelistParams params{};
    const auto response = client.get_futures_lead_trading_symbol_whitelist(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
