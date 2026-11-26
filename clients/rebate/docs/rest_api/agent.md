# TLS Agent

`agent` customises the TLS context before it is used: add certificate authorities, a client certificate, or verify certificates yourself. The system trust store is loaded first.

```cpp
#include <iostream>
#include <utility>

#include <boost/asio/ssl.hpp>

#include <binance/common/json.hpp>
#include <binance/rebate/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.agent = [](boost::asio::ssl::context& ctx) {
        // Trusted in addition to the system store, e.g. for a TLS-inspecting corporate proxy.
        ctx.load_verify_file("/path/to/ca.pem");
    };
    const auto client = rebate::RebateRestApi::production(std::move(cfg));

    using namespace rebate::rest_api;
    const GetSpotRebateHistoryRecordsParams params{};
    const auto response = client.get_spot_rebate_history_records(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
