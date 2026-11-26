# Key Pair Based Authentication

Signs requests with an RSA or Ed25519 key instead of an HMAC secret. The key is read on first use.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/algo/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    // RSA or Ed25519, as a file or inline with common::PrivateKey::from_pem(text).
    cfg.private_key = common::PrivateKey::from_file("/path/to/private_key.pem");
    cfg.private_key_passphrase = "passphrase";  // only for an encrypted key
    const auto client = algo::AlgoRestApi::production(std::move(cfg));

    using namespace algo::rest_api;
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams params{};
    const auto response = client.query_current_algo_open_orders_future_algo(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
