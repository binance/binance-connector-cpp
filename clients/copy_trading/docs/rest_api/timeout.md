# Timeout

How long one attempt of a request may take as a whole: DNS, connect, TLS handshake, writing the request and reading the whole response. A retry starts a new attempt. The default is 1000 ms.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/copy_trading/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timeout = std::chrono::milliseconds(5000);
    const auto client = copy_trading::CopyTradingRestApi::production(std::move(cfg));

    using namespace copy_trading::rest_api;
    const GetFuturesLeadTradingSymbolWhitelistParams params{};
    const auto response = client.get_futures_lead_trading_symbol_whitelist(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
