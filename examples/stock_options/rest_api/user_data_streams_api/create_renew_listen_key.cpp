//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <cstdlib>
#include <exception>
#include <string>
#include <utility>

#include <binance/common/json.hpp>
#include <binance/common/logger.hpp>
#include <binance/stock_options/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::stock_options::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = stock_options::StockOptionsRestApi::production(std::move(cfg));
        const CreateRenewListenKeyParams params{};
        const auto response = client.create_renew_listen_key(params);
        common::Logger::info("create_renew_listen_key() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("create_renew_listen_key() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("create_renew_listen_key() error: ") + e.what());
        return 1;
    }
}
