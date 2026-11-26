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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct GetFuturesPositionRiskOfSubAccountResponseInner {
    std::optional<std::string> entry_price;
    /// current initial leverage
    std::optional<std::string> leverage;
    /// notional value limit of current initial leverage
    std::optional<std::string> max_notional;
    std::optional<std::string> liquidation_price;
    std::optional<std::string> mark_price;
    std::optional<std::string> position_amount;
    std::optional<std::string> symbol;
    std::optional<std::string> unrealized_profit;

    bool
    operator==(const GetFuturesPositionRiskOfSubAccountResponseInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetFuturesPositionRiskOfSubAccountResponseInner
tag_invoke(boost::json::value_to_tag<GetFuturesPositionRiskOfSubAccountResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFuturesPositionRiskOfSubAccountResponseInner& v);

} // namespace binance::sub_account::rest_api
