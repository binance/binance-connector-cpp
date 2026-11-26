//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/query_user_wallet_balance_response_inner.hpp>

namespace binance::wallet::rest_api {

QueryUserWalletBalanceResponseInner
tag_invoke(boost::json::value_to_tag<QueryUserWalletBalanceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryUserWalletBalanceResponseInner");
    QueryUserWalletBalanceResponseInner out;
    common::detail::json::read(obj, "activate", out.activate);
    common::detail::json::read(obj, "balance", out.balance);
    common::detail::json::read(obj, "walletName", out.wallet_name);
    common::detail::json::read(obj, "assetBalances", out.asset_balances);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryUserWalletBalanceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "activate", v.activate);
    common::detail::json::write(obj, "balance", v.balance);
    common::detail::json::write(obj, "walletName", v.wallet_name);
    common::detail::json::write(obj, "assetBalances", v.asset_balances);
}

} // namespace binance::wallet::rest_api
