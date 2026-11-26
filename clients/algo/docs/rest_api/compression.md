# Compression

Responses are requested gzip / deflate compressed and decoded by default. `max_response_size` (128 MiB) caps the body before and after decompression.

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
    cfg.compression = false;
    cfg.max_response_size = 16ULL * 1024 * 1024;
    const auto client = algo::AlgoRestApi::production(std::move(cfg));

    using namespace algo::rest_api;
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{};
    const auto response = client.query_current_algo_open_orders_future_algo(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
