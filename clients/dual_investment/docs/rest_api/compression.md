# Compression

Responses are requested gzip / deflate compressed and decoded by default. `max_response_size` (128 MiB) caps the body before and after decompression.

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
    cfg.compression = false;
    cfg.max_response_size = 16ULL * 1024 * 1024;
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
