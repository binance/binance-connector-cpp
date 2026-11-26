//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response.hpp>

namespace binance::wallet::rest_api {

AssetDetailResponse tag_invoke(boost::json::value_to_tag<AssetDetailResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AssetDetailResponse");
    AssetDetailResponse out;
    common::detail::json::read(obj, "CTR", out.ctr);
    common::detail::json::read(obj, "SKY", out.sky);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AssetDetailResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "CTR", v.ctr);
    common::detail::json::write(obj, "SKY", v.sky);
}

} // namespace binance::wallet::rest_api
