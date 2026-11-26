# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

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
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = w3w_prediction::W3WPredictionRestApi::production(std::move(cfg));

    using namespace w3w_prediction::rest_api;
    const auto response = client.list_prediction_categories();
    std::cout << common::to_json(response.data()) << "\n";
}
```
