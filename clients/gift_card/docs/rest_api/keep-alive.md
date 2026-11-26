# Keep-Alive

Connections are reused between requests by default. Turn it off to open a new connection for every request.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/gift_card/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.keep_alive = false;
    const auto client = gift_card::GiftCardRestApi::production(std::move(cfg));

    using namespace gift_card::rest_api;
    const FetchRsaPublicKeyParams params{};
    const auto response = client.fetch_rsa_public_key(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
