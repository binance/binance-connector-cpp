# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/stock_options/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = stock_options::StockOptionsRestApi::production(std::move(cfg));

    using namespace stock_options::rest_api;
    const OptionContractsParams params{.underlying_symbol = "NVDA",
                                       .expiration_date = "2026-09-30"};
    const auto response = client.option_contracts(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
