# Timestamp Provider

The `timestamp` of signed requests comes from the host clock. When the host clock is off by more than `recvWindow` (error `-1021`), provide a corrected one. It is called once per attempt, possibly from the client thread: keep it cheap and thread-safe.

```cpp
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/alpha/rest_api.hpp>

using namespace binance;

// Host clock offset to Binance, in milliseconds: `serverTime` minus the local time, measured at
// start-up and refreshed from time to time (e.g. from the time endpoint).
std::atomic<std::int64_t> clock_offset{0};

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.timestamp_provider = [] {
        const auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now).count() + clock_offset.load();
    };
    const auto client = alpha::AlphaRestApi::production(std::move(cfg));

    using namespace alpha::rest_api;
    const auto response = client.get_exchange_info();
    std::cout << common::to_json(response.data()) << "\n";
}
```
