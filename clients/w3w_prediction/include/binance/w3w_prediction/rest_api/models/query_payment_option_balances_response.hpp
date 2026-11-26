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

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response_items_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryPaymentOptionBalancesResponse {
    std::optional<std::vector<QueryPaymentOptionBalancesResponseItemsInner>> items;

    bool operator==(const QueryPaymentOptionBalancesResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryPaymentOptionBalancesResponse
tag_invoke(boost::json::value_to_tag<QueryPaymentOptionBalancesResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryPaymentOptionBalancesResponse& v);

} // namespace binance::w3w_prediction::rest_api
