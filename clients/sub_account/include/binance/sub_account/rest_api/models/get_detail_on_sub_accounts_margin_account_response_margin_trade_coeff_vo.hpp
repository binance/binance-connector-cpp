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

struct GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo {
    /// Liquidation margin ratio
    std::optional<std::string> force_liquidation_bar;
    /// Margin call margin ratio
    std::optional<std::string> margin_call_bar;
    /// Initial margin ratio
    std::optional<std::string> normal_bar;

    bool operator==(const GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo
tag_invoke(boost::json::value_to_tag<
               GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDetailOnSubAccountsMarginAccountResponseMarginTradeCoeffVo& v);

} // namespace binance::sub_account::rest_api
