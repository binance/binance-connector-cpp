# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/dual_investment/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = dual_investment::DualInvestmentRestApi::production(std::move(cfg));

    using namespace dual_investment::rest_api;
    const GetDualInvestmentProductListParams params{
        .option_type = GetDualInvestmentProductListOptionTypeEnum::Call,
        .exercised_coin = "USDT",
        .invest_coin = "BNB"};
    const auto response = client.get_dual_investment_product_list(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
