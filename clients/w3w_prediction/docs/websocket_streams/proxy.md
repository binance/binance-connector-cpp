# Proxy

An HTTP or HTTPS proxy, reached with a `CONNECT` tunnel, or a SOCKS5 proxy. TLS and the WebSocket upgrade run end to end over it.

```cpp
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/w3w_prediction/websocket_streams.hpp>

using namespace binance;

int main() {
    common::WebsocketStreamsConfig cfg;
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
    auto client = w3w_prediction::W3WPredictionWebsocketStreams::production(std::move(cfg));
    auto connection = client.connect();

    using namespace w3w_prediction::websocket_streams;
    auto stream = connection.market_buy_order_failed();
    stream.on_message([](const auto& event) { std::cout << common::to_json(event) << "\n"; });
    std::this_thread::sleep_for(std::chrono::seconds(10));
    stream.unsubscribe();
    connection.disconnect();
}
```
