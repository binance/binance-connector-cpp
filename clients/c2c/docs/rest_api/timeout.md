# Timeout

How long one attempt of a request may take as a whole: DNS, connect, TLS handshake, writing the request and reading the whole response. A retry starts a new attempt. The default is 1000 ms.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/c2c/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timeout = std::chrono::milliseconds(5000);
    const auto client = c2c::C2CRestApi::production(std::move(cfg));

    using namespace c2c::rest_api;
    const GetC2CTradeHistoryParams params{};
    const auto response = client.get_c2c_trade_history(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
