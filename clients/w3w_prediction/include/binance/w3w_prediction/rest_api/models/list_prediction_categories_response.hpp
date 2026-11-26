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
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response_categories_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct ListPredictionCategoriesResponse {
    std::optional<std::vector<ListPredictionCategoriesResponseCategoriesInner>> categories;

    bool operator==(const ListPredictionCategoriesResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListPredictionCategoriesResponse
tag_invoke(boost::json::value_to_tag<ListPredictionCategoriesResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const ListPredictionCategoriesResponse& v);

} // namespace binance::w3w_prediction::rest_api
