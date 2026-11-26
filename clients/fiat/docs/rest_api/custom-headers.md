# Custom Headers

Headers added to every request. Join several values of one header with `", "`.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/fiat/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.custom_headers = {{"X-Request-Source", "my-app"}};
    const auto client = fiat::FiatRestApi::production(std::move(cfg));

    using namespace fiat::rest_api;
    const GetFiatDepositWithdrawHistoryParams params{.transaction_type = "0"};
    const auto response = client.get_fiat_deposit_withdraw_history(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
