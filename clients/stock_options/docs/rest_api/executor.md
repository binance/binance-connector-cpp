# Shared Event Loop

Each client runs its own I/O thread by default. Set `executor` to run many clients on one event loop. Keep the loop running while the clients have work, and do not make blocking calls from its threads.

```cpp
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>

#include <binance/common/json.hpp>
#include <binance/stock_options/rest_api.hpp>

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
        const auto client = stock_options::StockOptionsRestApi::production(std::move(cfg));

        using namespace stock_options::rest_api;
        const OptionContractsParams params{.underlying_symbol = "NVDA",
                                           .expiration_date = "2026-09-30"};
        const auto response = client.option_contracts(params);
        std::cout << common::to_json(response.data()) << "\n";
    }  // destroy the clients before stopping the loop
    work.reset();
    loop.join();
}
```
