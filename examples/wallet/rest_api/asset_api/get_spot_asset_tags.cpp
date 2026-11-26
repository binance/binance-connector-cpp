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
        const GetSpotAssetTagsParams params{};
        const auto response = client.get_spot_asset_tags(params);
        common::Logger::info("get_spot_asset_tags() rate limits: " +
                             common::to_json(response.rate_limits()));
        common::Logger::info("get_spot_asset_tags() response: " + common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(std::string("get_spot_asset_tags() error: ") + e.what());
        return 1;
    }
}
