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

struct GetFiatPaymentsHistoryResponseDataInner {
    std::optional<std::string> order_no;
    /// Fiat trade amount
    std::optional<std::string> source_amount;
    /// Fiat token
    std::optional<std::string> fiat_currency;
    /// Crypto trade amount
    std::optional<std::string> obtain_amount;
    /// Crypto token
    std::optional<std::string> crypto_currency;
    /// Trade fee
    std::optional<std::string> total_fee;
    /// Price
    std::optional<std::string> price;
    /// Processing, Completed, Failed, Refunded
    std::optional<std::string> status;
    /// Payment method
    std::optional<std::string> payment_method;
    /// Order create time
    std::optional<std::int64_t> create_time;
    /// Order update time
    std::optional<std::int64_t> update_time;

    bool operator==(const GetFiatPaymentsHistoryResponseDataInner& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT GetFiatPaymentsHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetFiatPaymentsHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetFiatPaymentsHistoryResponseDataInner& v);

} // namespace binance::fiat::rest_api
