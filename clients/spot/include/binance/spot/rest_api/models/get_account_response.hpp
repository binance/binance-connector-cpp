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
#include <binance/spot/rest_api/models/get_account_response_balances_inner.hpp>
#include <binance/spot/rest_api/models/get_account_response_commission_rates.hpp>

namespace binance::spot::rest_api {

struct GetAccountResponse {
    std::optional<std::int64_t> maker_commission;
    std::optional<std::int64_t> taker_commission;
    std::optional<std::int64_t> buyer_commission;
    std::optional<std::int64_t> seller_commission;
    std::optional<GetAccountResponseCommissionRates> commission_rates;
    std::optional<bool> can_trade;
    std::optional<bool> can_withdraw;
    std::optional<bool> can_deposit;
    std::optional<bool> brokered;
    std::optional<bool> require_self_trade_prevention;
    std::optional<bool> prevent_sor;
    std::optional<std::int64_t> update_time;
    std::optional<std::string> account_type;
    std::optional<std::vector<GetAccountResponseBalancesInner>> balances;
    std::optional<std::vector<std::string>> permissions;
    std::optional<std::int64_t> uid;

    bool operator==(const GetAccountResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT GetAccountResponse
tag_invoke(boost::json::value_to_tag<GetAccountResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetAccountResponse& v);

} // namespace binance::spot::rest_api
