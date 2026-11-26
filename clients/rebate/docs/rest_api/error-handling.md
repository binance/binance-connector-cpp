# Error Handling

Every error derives from `common::Error`, with the Binance `code()` and `msg()` when there is one. REST errors are subclasses of `common::ConnectorError` and carry the HTTP `response()` (headers and rate limits) when there was one. The full list is in [`common/README.md`](../../../../common/README.md#errors).

```cpp
#include <chrono>
#include <iostream>
#include <utility>

#include <binance/common/errors.hpp>
#include <binance/common/json.hpp>
#include <binance/rebate/rest_api.hpp>

using namespace binance;

int main() {
    common::RestApiConfig cfg;
    cfg.api_key = "your-api-key";
    cfg.api_secret = "your-api-secret";
    const auto client = rebate::RebateRestApi::production(std::move(cfg));

    using namespace rebate::rest_api;
    try {
        const GetSpotRebateHistoryRecordsParams params{};
        const auto response = client.get_spot_rebate_history_records(params);
        std::cout << common::to_json(response.data()) << "\n";
    } catch (const common::BadRequestError& e) {  // HTTP 400: invalid parameters
        std::cerr << "rejected: " << e.code().value_or(0) << " " << e.msg() << "\n";
    } catch (const common::TooManyRequestsError& e) {  // HTTP 429: back off
        std::cerr << "rate limited, retry after " << e.retry_after().value_or(std::chrono::seconds(60)).count() << " s\n";
    } catch (const common::RateLimitBanError& e) {  // HTTP 418: the IP is banned for a while
        std::cerr << "banned: " << e.msg() << "\n";
    } catch (const common::NetworkError& e) {
        // A request that may have reached Binance may also have been executed: check before
        // sending an order again.
        std::cerr << "network error, request sent: " << e.request_sent() << "\n";
    } catch (const common::ConnectorError& e) {  // any other HTTP or client error
        std::cerr << e.what() << "\n";
    }
}
```
