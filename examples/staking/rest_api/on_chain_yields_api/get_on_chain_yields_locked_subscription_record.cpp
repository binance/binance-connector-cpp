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
#include <binance/staking/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::staking::rest_api;

    common::RestApiConfig cfg;
    if (const char* key = std::getenv("API_KEY")) {
        cfg.api_key = key;
    }
    if (const char* secret = std::getenv("API_SECRET")) {
        cfg.api_secret = secret;
    }
    if (!cfg.api_key || !cfg.api_secret) {
        common::Logger::error("Set API_KEY and API_SECRET");
        return 1;
    }

    try {
        const auto client = staking::StakingRestApi::production(std::move(cfg));
        const GetOnChainYieldsLockedSubscriptionRecordParams params{};
        const auto response = client.get_on_chain_yields_locked_subscription_record(params);
        common::Logger::info("get_on_chain_yields_locked_subscription_record() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_on_chain_yields_locked_subscription_record() response: " +
                             common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(
            std::string("get_on_chain_yields_locked_subscription_record() error: ") + e.what());
        return 1;
    }
}
