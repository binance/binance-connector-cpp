# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/staking/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = staking::StakingRestApi::production(std::move(cfg));

    using namespace staking::rest_api;
    const EthStakingAccountParams params{};
    const auto response = client.eth_staking_account(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
