# Compression

Responses are requested gzip / deflate compressed and decoded by default. `max_response_size` (128 MiB) caps the body before and after decompression.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/vip_loan/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.compression = false;
    cfg.max_response_size = 16ULL * 1024 * 1024;
    const auto client = vip_loan::VipLoanRestApi::production(std::move(cfg));

    using namespace vip_loan::rest_api;
    const GetCollateralAssetDataParams params{};
    const auto response = client.get_collateral_asset_data(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
