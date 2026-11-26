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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner {
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<std::string> icon;
    std::optional<std::int64_t> order;

    bool
    operator==(const ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner& /*other*/)
        const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner
tag_invoke(boost::json::value_to_tag<
               ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ListPredictionCategoriesResponseCategoriesInnerSubcategoriesInner& v);

} // namespace binance::w3w_prediction::rest_api
