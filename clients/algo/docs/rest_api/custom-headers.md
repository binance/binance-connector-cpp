# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/algo/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = algo::AlgoRestApi::production(std::move(cfg));

    using namespace algo::rest_api;
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{};
    const auto response = client.query_current_algo_open_orders_future_algo(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
