//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response_regions_inner.hpp>

namespace binance::wallet::rest_api {

GetRegionListResponseRegionsInner
tag_invoke(boost::json::value_to_tag<GetRegionListResponseRegionsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetRegionListResponseRegionsInner");
    GetRegionListResponseRegionsInner out;
    common::detail::json::read(obj, "regionName", out.region_name);
    common::detail::json::read(obj, "blockType", out.block_type);
    common::detail::json::read(obj, "depositAllowed", out.deposit_allowed);
    common::detail::json::read(obj, "withdrawalAllowed", out.withdrawal_allowed);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRegionListResponseRegionsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "regionName", v.region_name);
    common::detail::json::write(obj, "blockType", v.block_type);
    common::detail::json::write(obj, "depositAllowed", v.deposit_allowed);
    common::detail::json::write(obj, "withdrawalAllowed", v.withdrawal_allowed);
}

} // namespace binance::wallet::rest_api
