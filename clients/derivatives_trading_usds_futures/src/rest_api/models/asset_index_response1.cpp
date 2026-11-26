//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/asset_index_response1.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

AssetIndexResponse1 tag_invoke(boost::json::value_to_tag<AssetIndexResponse1> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AssetIndexResponse1");
    AssetIndexResponse1 out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "time", out.time);
    common::detail::json::read(obj, "index", out.index);
    common::detail::json::read(obj, "bidBuffer", out.bid_buffer);
    common::detail::json::read(obj, "askBuffer", out.ask_buffer);
    common::detail::json::read(obj, "bidRate", out.bid_rate);
    common::detail::json::read(obj, "askRate", out.ask_rate);
    common::detail::json::read(obj, "autoExchangeBidBuffer", out.auto_exchange_bid_buffer);
    common::detail::json::read(obj, "autoExchangeAskBuffer", out.auto_exchange_ask_buffer);
    common::detail::json::read(obj, "autoExchangeBidRate", out.auto_exchange_bid_rate);
    common::detail::json::read(obj, "autoExchangeAskRate", out.auto_exchange_ask_rate);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AssetIndexResponse1& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "time", v.time);
    common::detail::json::write(obj, "index", v.index);
    common::detail::json::write(obj, "bidBuffer", v.bid_buffer);
    common::detail::json::write(obj, "askBuffer", v.ask_buffer);
    common::detail::json::write(obj, "bidRate", v.bid_rate);
    common::detail::json::write(obj, "askRate", v.ask_rate);
    common::detail::json::write(obj, "autoExchangeBidBuffer", v.auto_exchange_bid_buffer);
    common::detail::json::write(obj, "autoExchangeAskBuffer", v.auto_exchange_ask_buffer);
    common::detail::json::write(obj, "autoExchangeBidRate", v.auto_exchange_bid_rate);
    common::detail::json::write(obj, "autoExchangeAskRate", v.auto_exchange_ask_rate);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
