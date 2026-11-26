//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <map>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/pay/export.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryResponseDataInnerFundsDetailInner {
    /// Asset.
    std::optional<std::string> currency;
    /// Asset amount.
    std::optional<std::string> amount;
    /// Asset cost details per wallet type. Keys are wallet type IDs (e.g. "1", "2"), values are
    /// cost amounts.
    std::optional<std::map<std::string, std::string>> wallet_asset_cost;

    bool operator==(const GetPayTradeHistoryResponseDataInnerFundsDetailInner& /*other*/) const =
        default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponseDataInnerFundsDetailInner
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerFundsDetailInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponseDataInnerFundsDetailInner& v);

} // namespace binance::pay::rest_api
