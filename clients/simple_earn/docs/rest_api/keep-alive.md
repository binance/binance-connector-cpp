# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/simple_earn/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = simple_earn::SimpleEarnRestApi::production(std::move(cfg));

    using namespace simple_earn::rest_api;
    const GetBfusdAccountParams params{};
    const auto response = client.get_bfusd_account(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
