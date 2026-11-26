# TLS Agent

`agent` customises the TLS context before it is used: add certificate authorities, a client certificate, or verify certificates yourself. The system trust store is loaded first.

```cpp
#include <iostream>
#include <utility>

#include <boost/asio/ssl.hpp>

#include <binance/common/json.hpp>
#include <binance/sub_account/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.agent = [](boost::asio::ssl::context& ctx) {
        // Trusted in addition to the system store, e.g. for a TLS-inspecting corporate proxy.
        ctx.load_verify_file("/path/to/ca.pem");
    };
    const auto client = sub_account::SubAccountRestApi::production(std::move(cfg));

    using namespace sub_account::rest_api;
    const GetSubAccountsStatusOnMarginOrFuturesParams params{};
    const auto response = client.get_sub_accounts_status_on_margin_or_futures(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
