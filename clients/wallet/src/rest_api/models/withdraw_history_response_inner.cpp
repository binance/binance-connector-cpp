//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/withdraw_history_response_inner.hpp>

namespace binance::wallet::rest_api {

WithdrawHistoryResponseInner
tag_invoke(boost::json::value_to_tag<WithdrawHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "WithdrawHistoryResponseInner");
    WithdrawHistoryResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "transactionFee", out.transaction_fee);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "applyTime", out.apply_time);
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "transferType", out.transfer_type);
    common::detail::json::read(obj, "withdrawOrderId", out.withdraw_order_id);
    common::detail::json::read(obj, "info", out.info);
    common::detail::json::read(obj, "confirmNo", out.confirm_no);
    common::detail::json::read(obj, "walletType", out.wallet_type);
    common::detail::json::read(obj, "txKey", out.tx_key);
    common::detail::json::read(obj, "completeTime", out.complete_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const WithdrawHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "transactionFee", v.transaction_fee);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "applyTime", v.apply_time);
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "transferType", v.transfer_type);
    common::detail::json::write(obj, "withdrawOrderId", v.withdraw_order_id);
    common::detail::json::write(obj, "info", v.info);
    common::detail::json::write(obj, "confirmNo", v.confirm_no);
    common::detail::json::write(obj, "walletType", v.wallet_type);
    common::detail::json::write(obj, "txKey", v.tx_key);
    common::detail::json::write(obj, "completeTime", v.complete_time);
}

} // namespace binance::wallet::rest_api
