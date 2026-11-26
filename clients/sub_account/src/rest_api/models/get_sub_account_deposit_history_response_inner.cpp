//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/get_sub_account_deposit_history_response_inner.hpp>

namespace binance::sub_account::rest_api {

GetSubAccountDepositHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetSubAccountDepositHistoryResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetSubAccountDepositHistoryResponseInner");
    GetSubAccountDepositHistoryResponseInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "network", out.network);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "address", out.address);
    common::detail::json::read(obj, "addressTag", out.address_tag);
    common::detail::json::read(obj, "txId", out.tx_id);
    common::detail::json::read(obj, "insertTime", out.insert_time);
    common::detail::json::read(obj, "transferType", out.transfer_type);
    common::detail::json::read(obj, "confirmTimes", out.confirm_times);
    common::detail::json::read(obj, "unlockConfirm", out.unlock_confirm);
    common::detail::json::read(obj, "walletType", out.wallet_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetSubAccountDepositHistoryResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "network", v.network);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "address", v.address);
    common::detail::json::write(obj, "addressTag", v.address_tag);
    common::detail::json::write(obj, "txId", v.tx_id);
    common::detail::json::write(obj, "insertTime", v.insert_time);
    common::detail::json::write(obj, "transferType", v.transfer_type);
    common::detail::json::write(obj, "confirmTimes", v.confirm_times);
    common::detail::json::write(obj, "unlockConfirm", v.unlock_confirm);
    common::detail::json::write(obj, "walletType", v.wallet_type);
}

} // namespace binance::sub_account::rest_api
