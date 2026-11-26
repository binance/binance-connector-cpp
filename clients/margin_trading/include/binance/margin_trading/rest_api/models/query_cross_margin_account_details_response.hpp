//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_account_details_response_user_assets_inner.hpp>

namespace binance::margin_trading::rest_api {

struct QueryCrossMarginAccountDetailsResponse {
    /// True means margin account created , false means margin account not created.
    std::optional<bool> created;
    /// borrow Enabled.
    std::optional<bool> borrow_enabled;
    /// margin Level.
    std::optional<std::string> margin_level;
    /// collateral Margin Level.
    std::optional<std::string> collateral_margin_level;
    /// total Asset Of Btc.
    std::optional<std::string> total_asset_of_btc;
    /// total Liability Of Btc.
    std::optional<std::string> total_liability_of_btc;
    /// total Net Asset Of Btc.
    std::optional<std::string> total_net_asset_of_btc;
    /// Total Collateral Value In USDT.
    std::optional<std::string> total_collateral_value_in_usdt;
    /// trade Enabled.
    std::optional<bool> trade_enabled;
    /// transfer In Enabled.
    std::optional<bool> transfer_in_enabled;
    /// transfer Out Enabled.
    std::optional<bool> transfer_out_enabled;
    /// // MARGIN_1 for Cross Margin Classic, MARGIN_2 for Cross Margin Pro
    std::optional<std::string> account_type;
    /// user Assets list.
    std::optional<std::vector<QueryCrossMarginAccountDetailsResponseUserAssetsInner>> user_assets;

    bool operator==(const QueryCrossMarginAccountDetailsResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryCrossMarginAccountDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryCrossMarginAccountDetailsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryCrossMarginAccountDetailsResponse& v);

} // namespace binance::margin_trading::rest_api
