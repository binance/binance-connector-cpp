//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_cross_margin_account_details_response.hpp>

namespace binance::margin_trading::rest_api {

QueryCrossMarginAccountDetailsResponse
tag_invoke(boost::json::value_to_tag<QueryCrossMarginAccountDetailsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryCrossMarginAccountDetailsResponse");
    QueryCrossMarginAccountDetailsResponse out;
    common::detail::json::read(obj, "created", out.created);
    common::detail::json::read(obj, "borrowEnabled", out.borrow_enabled);
    common::detail::json::read(obj, "marginLevel", out.margin_level);
    common::detail::json::read(obj, "collateralMarginLevel", out.collateral_margin_level);
    common::detail::json::read(obj, "totalAssetOfBtc", out.total_asset_of_btc);
    common::detail::json::read(obj, "totalLiabilityOfBtc", out.total_liability_of_btc);
    common::detail::json::read(obj, "totalNetAssetOfBtc", out.total_net_asset_of_btc);
    common::detail::json::read(obj, "TotalCollateralValueInUSDT",
                               out.total_collateral_value_in_usdt);
    common::detail::json::read(obj, "tradeEnabled", out.trade_enabled);
    common::detail::json::read(obj, "transferInEnabled", out.transfer_in_enabled);
    common::detail::json::read(obj, "transferOutEnabled", out.transfer_out_enabled);
    common::detail::json::read(obj, "accountType", out.account_type);
    common::detail::json::read(obj, "userAssets", out.user_assets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryCrossMarginAccountDetailsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "created", v.created);
    common::detail::json::write(obj, "borrowEnabled", v.borrow_enabled);
    common::detail::json::write(obj, "marginLevel", v.margin_level);
    common::detail::json::write(obj, "collateralMarginLevel", v.collateral_margin_level);
    common::detail::json::write(obj, "totalAssetOfBtc", v.total_asset_of_btc);
    common::detail::json::write(obj, "totalLiabilityOfBtc", v.total_liability_of_btc);
    common::detail::json::write(obj, "totalNetAssetOfBtc", v.total_net_asset_of_btc);
    common::detail::json::write(obj, "TotalCollateralValueInUSDT",
                                v.total_collateral_value_in_usdt);
    common::detail::json::write(obj, "tradeEnabled", v.trade_enabled);
    common::detail::json::write(obj, "transferInEnabled", v.transfer_in_enabled);
    common::detail::json::write(obj, "transferOutEnabled", v.transfer_out_enabled);
    common::detail::json::write(obj, "accountType", v.account_type);
    common::detail::json::write(obj, "userAssets", v.user_assets);
}

} // namespace binance::margin_trading::rest_api
