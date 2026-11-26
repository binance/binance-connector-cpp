//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response.hpp>

namespace binance::wallet::rest_api {

GetRegionListResponse tag_invoke(boost::json::value_to_tag<GetRegionListResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetRegionListResponse");
    GetRegionListResponse out;
    common::detail::json::read(obj, "countryCode", out.country_code);
    common::detail::json::read(obj, "regions", out.regions);
    common::detail::json::read(obj, "lastUpdated", out.last_updated);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRegionListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "countryCode", v.country_code);
    common::detail::json::write(obj, "regions", v.regions);
    common::detail::json::write(obj, "lastUpdated", v.last_updated);
}

} // namespace binance::wallet::rest_api
