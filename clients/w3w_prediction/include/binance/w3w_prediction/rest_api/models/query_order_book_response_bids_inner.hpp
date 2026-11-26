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

struct QueryOrderBookResponseBidsInner {
    std::optional<std::string> price;
    std::optional<std::string> size;

    bool operator==(const QueryOrderBookResponseBidsInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryOrderBookResponseBidsInner
tag_invoke(boost::json::value_to_tag<QueryOrderBookResponseBidsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryOrderBookResponseBidsInner& v);

} // namespace binance::w3w_prediction::rest_api
