# Retries

GET and DELETE requests are retried on a network error or an HTTP 500 / 502 / 503 / 504, with a linear backoff: attempt `n` waits `n * backoff`. Each retry is signed again with a fresh `timestamp`. Requests that change the account (POST, PUT) are never retried.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/stock_options/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.retries = 5;  // attempts in total; 0 or 1 for a single one
    cfg.backoff = std::chrono::milliseconds(2000);
    const auto client = stock_options::StockOptionsRestApi::production(std::move(cfg));

    using namespace stock_options::rest_api;
    const OptionContractsParams params{.underlying_symbol = "NVDA",
                                       .expiration_date = "2026-09-30"};
    const auto response = client.option_contracts(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
