# Compression

Responses are requested gzip / deflate compressed and decoded by default. `max_response_size` (128 MiB) caps the body before and after decompression.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/copy_trading/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.compression = false;
    cfg.max_response_size = 16ULL * 1024 * 1024;
    const auto client = copy_trading::CopyTradingRestApi::production(std::move(cfg));

    using namespace copy_trading::rest_api;
    const GetFuturesLeadTradingSymbolWhitelistParams params{};
    const auto response = client.get_futures_lead_trading_symbol_whitelist(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
