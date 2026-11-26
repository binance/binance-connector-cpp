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

#include <binance/common/decimal.hpp>
#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct GetQuoteResponse {
    std::optional<std::string> quote_id;
    std::optional<std::string> token_id;
    std::optional<std::string> chance;
    std::optional<std::string> vendor;
    std::optional<std::string> market_title;
    std::optional<std::string> market_ext_id;
    std::optional<std::string> side;
    std::optional<std::string> amount_in;
    std::optional<std::string> amount_out;
    std::optional<bool> is_min_amount_out;
    std::optional<std::string> fee_amount;
    std::optional<std::string> fee_discount_bps;
    std::optional<common::Decimal> average_price;
    std::optional<common::Decimal> last_price;
    std::optional<common::Decimal> price_impact;
    std::optional<std::int64_t> timestamp;
    std::optional<std::string> chain_id;
    std::optional<std::int64_t> user_id;
    std::optional<std::string> wallet_address;
    std::optional<std::string> order_type;
    std::optional<std::int64_t> slippage_bps;
    std::optional<std::int64_t> fee_rate_bps;
    std::optional<std::string> min_receive;
    std::optional<std::int64_t> expire_at;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> price_limit;

    bool operator==(const GetQuoteResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetQuoteResponse
tag_invoke(boost::json::value_to_tag<GetQuoteResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv, const GetQuoteResponse& v);

} // namespace binance::w3w_prediction::rest_api
