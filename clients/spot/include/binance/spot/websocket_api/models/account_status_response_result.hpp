//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/account_status_response_result_balances_inner.hpp>
#include <binance/spot/websocket_api/models/account_status_response_result_commission_rates.hpp>

namespace binance::spot::websocket_api {

struct AccountStatusResponseResult {
    std::optional<std::int64_t> maker_commission;
    std::optional<std::int64_t> taker_commission;
    std::optional<std::int64_t> buyer_commission;
    std::optional<std::int64_t> seller_commission;
    std::optional<bool> can_trade;
    std::optional<bool> can_withdraw;
    std::optional<bool> can_deposit;
    std::optional<AccountStatusResponseResultCommissionRates> commission_rates;
    std::optional<bool> brokered;
    std::optional<bool> require_self_trade_prevention;
    std::optional<bool> prevent_sor;
    std::optional<std::int64_t> update_time;
    std::optional<std::string> account_type;
    std::optional<std::vector<AccountStatusResponseResultBalancesInner>> balances;
    std::optional<std::vector<std::string>> permissions;
    std::optional<std::int64_t> uid;

    bool operator==(const AccountStatusResponseResult& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountStatusResponseResult tag_invoke(
    boost::json::value_to_tag<AccountStatusResponseResult> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountStatusResponseResult& v);

} // namespace binance::spot::websocket_api
