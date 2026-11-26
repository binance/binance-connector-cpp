//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

AccountBlockTradeListResponseInner
tag_invoke(boost::json::value_to_tag<AccountBlockTradeListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AccountBlockTradeListResponseInner");
    AccountBlockTradeListResponseInner out;
    common::detail::json::read(obj, "parentOrderId", out.parent_order_id);
    common::detail::json::read(obj, "crossType", out.cross_type);
    common::detail::json::read(obj, "legs", out.legs);
    common::detail::json::read(obj, "blockTradeSettlementKey", out.block_trade_settlement_key);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AccountBlockTradeListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "parentOrderId", v.parent_order_id);
    common::detail::json::write(obj, "crossType", v.cross_type);
    common::detail::json::write(obj, "legs", v.legs);
    common::detail::json::write(obj, "blockTradeSettlementKey", v.block_trade_settlement_key);
}

} // namespace binance::derivatives_trading_options::rest_api
