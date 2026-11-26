# Key Pair Based Authentication

Signs requests with an RSA or Ed25519 key instead of an HMAC secret. With an Ed25519 key, `session_logon()` (when the API has it) authenticates the connection once instead.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_api.hpp>

using namespace binance;

int main() {
    common::WebsocketApiConfig cfg;
    cfg.api_key = "your-api-key";
    // RSA or Ed25519, as a file or inline with common::PrivateKey::from_pem(text).
    cfg.private_key = common::PrivateKey::from_file("/path/to/private_key.pem");
    cfg.private_key_passphrase = "passphrase";  // only for an encrypted key
    auto client = derivatives_trading_usds_futures::DerivativesTradingUsdsFuturesWebsocketApi::production(std::move(cfg));
    auto connection = client.connect();

    using namespace derivatives_trading_usds_futures::websocket_api;
    const SymbolOrderBookTickerParams params{};
    const auto response = connection.symbol_order_book_ticker(params);
    std::cout << common::to_json(response.data()) << "\n";
    connection.disconnect();
}
```
