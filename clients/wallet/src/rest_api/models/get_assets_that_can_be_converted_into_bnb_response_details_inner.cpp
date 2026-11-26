//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response_details_inner.hpp>

namespace binance::wallet::rest_api {

GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner tag_invoke(
    boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner> /*tag*/,
    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner");
    GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner out;
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "assetFullName", out.asset_full_name);
    common::detail::json::read(obj, "amountFree", out.amount_free);
    common::detail::json::read(obj, "toBTC", out.to_btc);
    common::detail::json::read(obj, "toBNB", out.to_bnb);
    common::detail::json::read(obj, "toBNBOffExchange", out.to_bnb_off_exchange);
    common::detail::json::read(obj, "exchange", out.exchange);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "assetFullName", v.asset_full_name);
    common::detail::json::write(obj, "amountFree", v.amount_free);
    common::detail::json::write(obj, "toBTC", v.to_btc);
    common::detail::json::write(obj, "toBNB", v.to_bnb);
    common::detail::json::write(obj, "toBNBOffExchange", v.to_bnb_off_exchange);
    common::detail::json::write(obj, "exchange", v.exchange);
}

} // namespace binance::wallet::rest_api
