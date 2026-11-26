//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

NewBlockTradeOrderResponse tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "NewBlockTradeOrderResponse");
    NewBlockTradeOrderResponse out;
    common::detail::json::read(obj, "blockTradeSettlementKey", out.block_trade_settlement_key);
    common::detail::json::read(obj, "expireTime", out.expire_time);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "legs", out.legs);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const NewBlockTradeOrderResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "blockTradeSettlementKey", v.block_trade_settlement_key);
    common::detail::json::write(obj, "expireTime", v.expire_time);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "legs", v.legs);
}

} // namespace binance::derivatives_trading_options::rest_api
