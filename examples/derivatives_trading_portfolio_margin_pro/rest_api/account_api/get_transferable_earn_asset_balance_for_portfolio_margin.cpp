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
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api.hpp>

int main() {
    using namespace binance;
    using namespace binance::derivatives_trading_portfolio_margin_pro::rest_api;

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
        const auto client = derivatives_trading_portfolio_margin_pro::
            DerivativesTradingPortfolioMarginProRestApi::production(std::move(cfg));
        const GetTransferableEarnAssetBalanceForPortfolioMarginParams params{
            .asset = "LDUSDT",
            .transfer_type =
                GetTransferableEarnAssetBalanceForPortfolioMarginTransferTypeEnum::EarnToFuture};
        const auto response =
            client.get_transferable_earn_asset_balance_for_portfolio_margin(params);
        common::Logger::info(
            "get_transferable_earn_asset_balance_for_portfolio_margin() rate limits: " +
            common::to_json(response.rate_limits()));
        common::Logger::info(
            "get_transferable_earn_asset_balance_for_portfolio_margin() response: " +
            common::to_json(response.data()));
    } catch (const std::exception& e) {
        common::Logger::error(
            std::string("get_transferable_earn_asset_balance_for_portfolio_margin() error: ") +
            e.what());
        return 1;
    }
}
