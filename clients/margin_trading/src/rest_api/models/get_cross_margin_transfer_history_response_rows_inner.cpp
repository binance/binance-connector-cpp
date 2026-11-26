//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_cross_margin_transfer_history_response_rows_inner.hpp>

namespace binance::margin_trading::rest_api {

GetCrossMarginTransferHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetCrossMarginTransferHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetCrossMarginTransferHistoryResponseRowsInner");
    GetCrossMarginTransferHistoryResponseRowsInner out;
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "transFrom", out.trans_from);
    common::detail::json::read(obj, "transTo", out.trans_to);
    common::detail::json::read(obj, "fromSymbol", out.from_symbol);
    common::detail::json::read(obj, "toSymbol", out.to_symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCrossMarginTransferHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "timestamp", v.timestamp);
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "transFrom", v.trans_from);
    common::detail::json::write(obj, "transTo", v.trans_to);
    common::detail::json::write(obj, "fromSymbol", v.from_symbol);
    common::detail::json::write(obj, "toSymbol", v.to_symbol);
}

} // namespace binance::margin_trading::rest_api
