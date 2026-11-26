//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/composite_index_symbol_information_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

CompositeIndexSymbolInformationResponseInner
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "CompositeIndexSymbolInformationResponseInner");
    CompositeIndexSymbolInformationResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "component", out.component);
    common::detail::json::read(obj, "baseAssetList", out.base_asset_list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CompositeIndexSymbolInformationResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "component", v.component);
    common::detail::json::write(obj, "baseAssetList", v.base_asset_list);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
