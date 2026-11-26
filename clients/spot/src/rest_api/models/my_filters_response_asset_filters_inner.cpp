//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <string_view>
#include <variant>

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/models/my_filters_response_asset_filters_inner.hpp>

namespace binance::spot::rest_api {

MyFiltersResponseAssetFiltersInner
tag_invoke(boost::json::value_to_tag<MyFiltersResponseAssetFiltersInner> /*tag*/,
           const boost::json::value& jv) {
    MyFiltersResponseAssetFiltersInner out;
    if (const auto* obj = jv.if_object()) {
        if (const auto* tag = obj->if_contains("filterType"); tag != nullptr && tag->is_string()) {
            const std::string_view name = tag->get_string();
            if (name == "MAX_ASSET") {
                out.value = boost::json::value_to<MaxAssetFilter>(jv);
                return out;
            }
        }
    }
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const MyFiltersResponseAssetFiltersInner& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
    // The alternatives do not store the tag that selected them.
    auto* obj = jv.if_object();
    if (obj == nullptr || obj->contains("filterType")) {
        return;
    }
    if (std::holds_alternative<MaxAssetFilter>(v.value)) {
        (*obj)["filterType"] = "MAX_ASSET";
        return;
    }
}

} // namespace binance::spot::rest_api
