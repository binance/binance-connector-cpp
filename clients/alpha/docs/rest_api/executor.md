# Shared Event Loop

Each client runs its own I/O thread by default. Set `executor` to run many clients on one event loop. Keep the loop running while the clients have work, and do not make blocking calls from its threads.

```cpp
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>

#include <binance/common/json.hpp>
#include <binance/alpha/rest_api.hpp>

using namespace binance;

int main() {
    boost::asio::io_context ioc;
    auto work = boost::asio::make_work_guard(ioc);
    std::thread loop([&ioc] { ioc.run(); });
    {
        common::RestApiConfig cfg;
        cfg.api_key = "your-api-key";
        cfg.api_secret = "your-api-secret";
        cfg.executor = ioc.get_executor();
        const auto client = alpha::AlphaRestApi::production(std::move(cfg));

        using namespace alpha::rest_api;
        const auto response = client.get_exchange_info();
        std::cout << common::to_json(response.data()) << "\n";
    }  // destroy the clients before stopping the loop
    work.reset();
    loop.join();
}
```
