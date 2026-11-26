//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trading_symbol_whitelist_response_data_inner.hpp>

namespace binance::copy_trading::rest_api {

GetFuturesLeadTradingSymbolWhitelistResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFuturesLeadTradingSymbolWhitelistResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(
        jv, "GetFuturesLeadTradingSymbolWhitelistResponseDataInner");
    GetFuturesLeadTradingSymbolWhitelistResponseDataInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "baseAsset", out.base_asset);
    common::detail::json::read(obj, "quoteAsset", out.quote_asset);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFuturesLeadTradingSymbolWhitelistResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "baseAsset", v.base_asset);
    common::detail::json::write(obj, "quoteAsset", v.quote_asset);
}

} // namespace binance::copy_trading::rest_api
