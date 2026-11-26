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

#include <binance/derivatives_trading_portfolio_margin_pro/export.hpp>
#include <binance/derivatives_trading_portfolio_margin_pro/rest_api/models/get_portfolio_margin_pro_span_account_info_response_risk_unit_mm_list_inner.hpp>

namespace binance::derivatives_trading_portfolio_margin_pro::rest_api {

struct GetPortfolioMarginProSpanAccountInfoResponse {
    /// uni MMR.
    std::optional<std::string> uni_mmr;
    /// Account equity, unit：USD
    std::optional<std::string> account_equity;
    /// Actual equity, unit：USD
    std::optional<std::string> actual_equity;
    /// Account maintenance margin, unit：USD
    std::optional<std::string> account_maint_margin;
    std::optional<std::vector<GetPortfolioMarginProSpanAccountInfoResponseRiskUnitMMListInner>>
        risk_unit_mm_list;
    /// margin MM.
    std::optional<std::string> margin_mm;
    /// other MM.
    std::optional<std::string> other_mm;
    /// Classic Portfolio margin account status:"NORMAL", "MARGIN_CALL", "SUPPLY_MARGIN",
    /// "REDUCE_ONLY", "ACTIVE_LIQUIDATION", "FORCE_LIQUIDATION", "BANKRUPTED"
    std::optional<std::string> account_status;
    /// PM_1 for classic PM, PM_2 for PM, PM_3 for PM Pro(SPAN)
    std::optional<std::string> account_type;

    bool operator==(const GetPortfolioMarginProSpanAccountInfoResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT GetPortfolioMarginProSpanAccountInfoResponse
tag_invoke(boost::json::value_to_tag<GetPortfolioMarginProSpanAccountInfoResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_PRO_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetPortfolioMarginProSpanAccountInfoResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin_pro::rest_api
