//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/query_user_wallet_balance_response_inner_asset_balances_inner.hpp>

namespace binance::wallet::rest_api {

struct QueryUserWalletBalanceResponseInner {
    std::optional<bool> activate;
    std::optional<std::string> balance;
    std::optional<std::string> wallet_name;
    /// Per-asset balance detail for this wallet. Only present when `needBalanceDetail=true` is
    /// passed; omitted entirely otherwise.
    std::optional<std::vector<QueryUserWalletBalanceResponseInnerAssetBalancesInner>>
        asset_balances;

    bool operator==(const QueryUserWalletBalanceResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT QueryUserWalletBalanceResponseInner
tag_invoke(boost::json::value_to_tag<QueryUserWalletBalanceResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const QueryUserWalletBalanceResponseInner& v);

} // namespace binance::wallet::rest_api
