# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/sub_account/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = sub_account::SubAccountRestApi::production(std::move(cfg));

    using namespace sub_account::rest_api;
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    const auto response = client.get_sub_accounts_status_on_margin_or_futures(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
