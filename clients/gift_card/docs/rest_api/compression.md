# Compression

Responses are requested gzip / deflate compressed and decoded by default. `max_response_size` (128 MiB) caps the body before and after decompression.

```cpp
#include <iostream>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/gift_card/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    cfg.compression = false;
    cfg.max_response_size = 16ULL * 1024 * 1024;
    const auto client = gift_card::GiftCardRestApi::production(std::move(cfg));

    using namespace gift_card::rest_api;
    const FetchRsaPublicKeyParams params{};
    const auto response = client.fetch_rsa_public_key(params);
    std::cout << common::to_json(response.data()) << "\n";
}
```
