# Key Pair Based Authentication

Signs the connection URLs of the signed streams with an RSA or Ed25519 key instead of an HMAC secret.

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
    // RSA or Ed25519, as a file or inline with common::PrivateKey::from_pem(text).
    cfg.private_key = common::PrivateKey::from_file("/path/to/private_key.pem");
    cfg.private_key_passphrase = "passphrase";  // only for an encrypted key
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
