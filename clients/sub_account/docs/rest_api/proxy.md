# Proxy

An HTTP or HTTPS proxy (with Basic authentication), or a SOCKS5 proxy. Requests to `https://` endpoints go through a `CONNECT` tunnel, so TLS runs end to end.

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
    cfg.proxy = common::ProxyConfig{
        .host = "127.0.0.1",
        .port = 8080,
        .protocol = common::ProxyProtocol::Http,  // Https, Socks5 or Socks5h (the proxy resolves)
        .auth = common::ProxyAuth{.username = "user", .password = "password"},
    };
    // Without `proxy`, HTTPS_PROXY / HTTP_PROXY / ALL_PROXY / NO_PROXY are used unless:
    // cfg.proxy_from_env = false;
    const auto client = sub_account::SubAccountRestApi::production(std::move(cfg));

    using namespace sub_account::rest_api;
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    const auto response = client.get_sub_accounts_status_on_margin_or_futures(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
