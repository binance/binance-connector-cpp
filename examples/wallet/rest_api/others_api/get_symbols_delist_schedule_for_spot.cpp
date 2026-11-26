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
#include <binance/wallet/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::wallet::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }

    try {
        const auto client = wallet::WalletRestApi::production(std::move(cfg));
        const GetSymbolsDelistScheduleForSpotParams params{};
        const auto response = client.get_symbols_delist_schedule_for_spot(params);
        common::Logger::info("get_symbols_delist_schedule_for_spot() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_symbols_delist_schedule_for_spot() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("get_symbols_delist_schedule_for_spot() error: ") +
                              e.what());
        return 1;
    }
}
