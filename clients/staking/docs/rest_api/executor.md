# Shared Event Loop

Each client runs its own I/O thread by default. Set `executor` to run many clients on one event loop. Keep the loop running while the clients have work, and do not make blocking calls from its threads.

```cpp
#include <iostream>
#include <thread>
#include <utility>

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>

#include <binance/common/json.hpp>
#include <binance/staking/rest_api.hpp>

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
        const auto client = staking::StakingRestApi::production(std::move(cfg));

        using namespace staking::rest_api;
        const EthStakingAccountParams params{};
        const auto response = client.eth_staking_account(params);
        std::cout << common::to_json(response.data()) << "\n";
    }  // destroy the clients before stopping the loop
    work.reset();
    loop.join();
}
```
