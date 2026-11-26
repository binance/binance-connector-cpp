# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesRestApi::production(std::move(cfg));

    using namespace derivatives_trading_usds_futures::rest_api;
    const AdlRiskParams params{};
    const auto response = client.adl_risk(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
