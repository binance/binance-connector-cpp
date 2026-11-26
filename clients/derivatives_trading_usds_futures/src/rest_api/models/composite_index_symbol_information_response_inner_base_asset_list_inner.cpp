//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/composite_index_symbol_information_response_inner_base_asset_list_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

CompositeIndexSymbolInformationResponseInnerBaseAssetListInner
tag_invoke(boost::json::value_to_tag<
               CompositeIndexSymbolInformationResponseInnerBaseAssetListInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "CompositeIndexSymbolInformationResponseInnerBaseAssetListInner");
    CompositeIndexSymbolInformationResponseInnerBaseAssetListInner out;
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    common::detail::json::read(obj, "weightInQuantity", out.weight_in_quantity);
    common::detail::json::read(obj, "weightInPercentage", out.weight_in_percentage);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CompositeIndexSymbolInformationResponseInnerBaseAssetListInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
    common::detail::json::write(obj, "weightInQuantity", v.weight_in_quantity);
    common::detail::json::write(obj, "weightInPercentage", v.weight_in_percentage);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
