//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response.hpp>

namespace binance::wallet::rest_api {

GetAssetsThatCanBeConvertedIntoBnbResponse
tag_invoke(boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetAssetsThatCanBeConvertedIntoBnbResponse");
    GetAssetsThatCanBeConvertedIntoBnbResponse out;
    common::detail::json::read(obj, "details", out.details);
    common::detail::json::read(obj, "totalTransferBtc", out.total_transfer_btc);
    common::detail::json::read(obj, "totalTransferBNB", out.total_transfer_bnb);
    common::detail::json::read(obj, "dribbletPercentage", out.dribblet_percentage);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetAssetsThatCanBeConvertedIntoBnbResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "details", v.details);
    common::detail::json::write(obj, "totalTransferBtc", v.total_transfer_btc);
    common::detail::json::write(obj, "totalTransferBNB", v.total_transfer_bnb);
    common::detail::json::write(obj, "dribbletPercentage", v.dribblet_percentage);
}

} // namespace binance::wallet::rest_api
