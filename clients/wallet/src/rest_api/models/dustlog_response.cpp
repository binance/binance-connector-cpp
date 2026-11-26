//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dustlog_response.hpp>

namespace binance::wallet::rest_api {

DustlogResponse tag_invoke(boost::json::value_to_tag<DustlogResponse> /*tag*/,
                           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DustlogResponse");
    DustlogResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "userAssetDribblets", out.user_asset_dribblets);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustlogResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "userAssetDribblets", v.user_asset_dribblets);
}

} // namespace binance::wallet::rest_api
