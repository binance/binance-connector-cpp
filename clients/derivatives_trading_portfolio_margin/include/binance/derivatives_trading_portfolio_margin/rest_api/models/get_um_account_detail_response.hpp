//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/derivatives_trading_portfolio_margin/export.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_account_detail_response_assets_inner.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_account_detail_response_positions_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetUmAccountDetailResponse {
    /// Assets.
    std::optional<std::vector<GetUmAccountDetailResponseAssetsInner>> assets;
    /// positions of all symbols in the market are returned
    std::optional<std::vector<GetUmAccountDetailResponsePositionsInner>> positions;

    bool operator==(const GetUmAccountDetailResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUmAccountDetailResponse tag_invoke(
    boost::json::value_to_tag<GetUmAccountDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetUmAccountDetailResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
