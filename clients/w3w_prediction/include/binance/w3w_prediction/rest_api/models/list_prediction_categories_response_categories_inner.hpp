//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response_categories_inner_subcategories_inner.hpp>

namespace binance::w3w_prediction::rest_api {

struct ListPredictionCategoriesResponseCategoriesInner {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<std::string> icon;
    std::optional<std::int64_t> order;
    std::optional<std::vector<ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner>>
        subcategories;

    bool
    operator==(const ListPredictionCategoriesResponseCategoriesInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListPredictionCategoriesResponseCategoriesInner
tag_invoke(boost::json::value_to_tag<ListPredictionCategoriesResponseCategoriesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ListPredictionCategoriesResponseCategoriesInner& v);

} // namespace binance::w3w_prediction::rest_api
