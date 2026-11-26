# Reconnect Delay

Delay before reconnecting a connection that dropped (5000 ms by default). After a failed attempt, a backoff of 1 s doubling up to 60 s, with random jitter, is added to it. Requests fail with `WebsocketNotConnectedError` while there is no connection.

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.reconnect_delay = std::chrono::milliseconds(1000);
    auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_coin_futures::websocket_api;
    const AccountInformationParams params{};
    const auto response = connection.account_information(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
