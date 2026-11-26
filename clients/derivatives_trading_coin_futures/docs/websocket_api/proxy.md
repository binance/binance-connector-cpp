# Proxy

An HTTP or HTTPS proxy, reached with a `CONNECT` tunnel, or a SOCKS5 proxy. TLS and the WebSocket upgrade run end to end over it.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.proxy = common::ProxyConfig{
        .host = "127.0.0.1",
        .port = 8080,
        .protocol = common::ProxyProtocol::Http,  // Https, Socks5 or Socks5h (the proxy resolves)
        .auth = common::ProxyAuth{.username = "user", .password = "password"},
    };
    // Without `proxy`, the proxy from HTTPS_PROXY / ALL_PROXY / NO_PROXY is used only with:
    // cfg.proxy_from_env = true;
    auto client = derivatives_trading_coin_futures::DerivativesTradingCoinFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_coin_futures::websocket_api;
    const AccountInformationParams params{};
    const auto response = connection.account_information(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
