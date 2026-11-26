//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response_categories_inner.hpp>

namespace binance::w3w_prediction::rest_api {

ListPredictionCategoriesResponseCategoriesInner
tag_invoke(boost::json::value_to_tag<ListPredictionCategoriesResponseCategoriesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "ListPredictionCategoriesResponseCategoriesInner");
    ListPredictionCategoriesResponseCategoriesInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "icon", out.icon);
    common::detail::json::read(obj, "order", out.order);
    common::detail::json::read(obj, "subcategories", out.subcategories);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ListPredictionCategoriesResponseCategoriesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "icon", v.icon);
    common::detail::json::write(obj, "order", v.order);
    common::detail::json::write(obj, "subcategories", v.subcategories);
}

} // namespace binance::w3w_prediction::rest_api
