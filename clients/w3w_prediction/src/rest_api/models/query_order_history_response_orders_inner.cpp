//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_history_response_orders_inner.hpp>

namespace binance::w3w_prediction::rest_api {

QueryOrderHistoryResponseOrdersInner
tag_invoke(boost::json::value_to_tag<QueryOrderHistoryResponseOrdersInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryOrderHistoryResponseOrdersInner");
    QueryOrderHistoryResponseOrdersInner out;
    common::detail::json::read(obj, "orderId", out.order_id);
    common::detail::json::read(obj, "vendorOrderId", out.vendor_order_id);
    common::detail::json::read(obj, "vendor", out.vendor);
    common::detail::json::read(obj, "marketTopicId", out.market_topic_id);
    common::detail::json::read(obj, "slug", out.slug);
    common::detail::json::read(obj, "marketTopicTitle", out.market_topic_title);
    common::detail::json::read(obj, "marketId", out.market_id);
    common::detail::json::read(obj, "marketTitle", out.market_title);
    common::detail::json::read(obj, "outcome", out.outcome);
    common::detail::json::read(obj, "outcomeIndex", out.outcome_index);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "side", out.side);
    common::detail::json::read(obj, "orderType", out.order_type);
    common::detail::json::read(obj, "createTime", out.create_time);
    common::detail::json::read(obj, "modifyTime", out.modify_time);
    common::detail::json::read(obj, "terminalTime", out.terminal_time);
    common::detail::json::read(obj, "makerUsdtAmount", out.maker_usdt_amount);
    common::detail::json::read(obj, "makerShareQty", out.maker_share_qty);
    common::detail::json::read(obj, "filledUsdtAmount", out.filled_usdt_amount);
    common::detail::json::read(obj, "filledShareQty", out.filled_share_qty);
    common::detail::json::read(obj, "fillPercentage", out.fill_percentage);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "marketProviderFee", out.market_provider_fee);
    common::detail::json::read(obj, "networkFee", out.network_fee);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryOrderHistoryResponseOrdersInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "orderId", v.order_id);
    common::detail::json::write(obj, "vendorOrderId", v.vendor_order_id);
    common::detail::json::write(obj, "vendor", v.vendor);
    common::detail::json::write(obj, "marketTopicId", v.market_topic_id);
    common::detail::json::write(obj, "slug", v.slug);
    common::detail::json::write(obj, "marketTopicTitle", v.market_topic_title);
    common::detail::json::write(obj, "marketId", v.market_id);
    common::detail::json::write(obj, "marketTitle", v.market_title);
    common::detail::json::write(obj, "outcome", v.outcome);
    common::detail::json::write(obj, "outcomeIndex", v.outcome_index);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "side", v.side);
    common::detail::json::write(obj, "orderType", v.order_type);
    common::detail::json::write(obj, "createTime", v.create_time);
    common::detail::json::write(obj, "modifyTime", v.modify_time);
    common::detail::json::write(obj, "terminalTime", v.terminal_time);
    common::detail::json::write(obj, "makerUsdtAmount", v.maker_usdt_amount);
    common::detail::json::write(obj, "makerShareQty", v.maker_share_qty);
    common::detail::json::write(obj, "filledUsdtAmount", v.filled_usdt_amount);
    common::detail::json::write(obj, "filledShareQty", v.filled_share_qty);
    common::detail::json::write(obj, "fillPercentage", v.fill_percentage);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "marketProviderFee", v.market_provider_fee);
    common::detail::json::write(obj, "networkFee", v.network_fee);
}

} // namespace binance::w3w_prediction::rest_api
