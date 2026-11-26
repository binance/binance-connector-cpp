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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/fiat/export.hpp>

namespace binance::fiat::rest_api {

struct GetFiatDepositWithdrawHistoryResponseDataInner {
    std::optional<std::string> order_no;
    /// Fiat token
    std::optional<std::string> fiat_currency;
    /// Trade amount
    std::optional<std::string> indicated_amount;
    /// Actual amount (after fee deduction)
    std::optional<std::string> amount;
    /// Trade fee
    std::optional<std::string> total_fee;
    /// Trade method
    std::optional<std::string> method;
    /// Processing, Failed, Successful, Finished, Refunding, Refunded, Refund Failed, Order Partial
    /// Credit Stopped
    std::optional<std::string> status;
    /// Order create time
    std::optional<std::int64_t> create_time;
    /// Order update time
    std::optional<std::int64_t> update_time;

    bool
    operator==(const GetFiatDepositWithdrawHistoryResponseDataInner& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT GetFiatDepositWithdrawHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFiatDepositWithdrawHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetFiatDepositWithdrawHistoryResponseDataInner& v);

} // namespace binance::fiat::rest_api
