# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/w3w_prediction/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = w3w_prediction::W3WPredictionRestApi::production(std::move(cfg));

    using namespace w3w_prediction::rest_api;
    const auto response = client.list_prediction_categories();
    std::cout << common::to_json(response.data()) << "\n";
}
```
