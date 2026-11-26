# Timeout

How long one attempt of a request may take as a whole: DNS, connect, TLS handshake, writing the request and reading the whole response. A retry starts a new attempt. The default is 1000 ms.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/margin_trading/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timeout = std::chrono::milliseconds(5000);
    const auto client = margin_trading::MarginTradingRestApi::production(std::move(cfg));

    using namespace margin_trading::rest_api;
    const auto response = client.cross_margin_collateral_ratio();
    std::cout << common::to_json(response.data()) << "\n";
}
```
