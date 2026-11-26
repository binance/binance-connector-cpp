# Key Pair Based Authentication

Signs requests with an RSA or Ed25519 key instead of an HMAC secret. The key is read on first use.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/sub_account/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    // RSA or Ed25519, as a file or inline with common::PrivateKey::from_pem(text).
    cfg.private_key = common::PrivateKey::from_file("/path/to/private_key.pem");
    cfg.private_key_passphrase = "passphrase";  // only for an encrypted key
    const auto client = sub_account::SubAccountRestApi::production(std::move(cfg));

    using namespace sub_account::rest_api;
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    const auto response = client.get_sub_accounts_status_on_margin_or_futures(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
