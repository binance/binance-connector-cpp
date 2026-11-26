# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/spot/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = spot::SpotRestApi::production(std::move(cfg));

    using namespace spot::rest_api;
    const ExchangeInfoParams params{};
    const auto response = client.exchange_info(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
