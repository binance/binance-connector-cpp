//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response.hpp>

namespace binance::w3w_prediction::rest_api {

ListPredictionCategoriesResponse
tag_invoke(boost::json::value_to_tag<ListPredictionCategoriesResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ListPredictionCategoriesResponse");
    ListPredictionCategoriesResponse out;
    common::detail::json::read(obj, "categories", out.categories);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListPredictionCategoriesResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "categories", v.categories);
}

} // namespace binance::w3w_prediction::rest_api
