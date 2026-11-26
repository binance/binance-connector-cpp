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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryPaymentOptionBalancesResponseItemsInner {
    std::optional<std::string> account_type;
    std::optional<std::string> available_balance_display;
    std::optional<bool> enabled;

    bool operator==(const QueryPaymentOptionBalancesResponseItemsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPaymentOptionBalancesResponseItemsInner
tag_invoke(boost::json::value_to_tag<QueryPaymentOptionBalancesResponseItemsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryPaymentOptionBalancesResponseItemsInner& v);

} // namespace binance::w3w_prediction::rest_api
