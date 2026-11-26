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

struct ListOtcBlocktradesResponseBlocktradesInner {
    std::optional<std::string> status;
    std::optional<std::string> market_id;
    std::optional<std::string> token_id;
    /// 0 = BUY (Bid), 1 = SELL (Ask) — see Create OTC Blocktrade for the side/quoteType mapping
    std::optional<std::int64_t> side;
    std::optional<std::string> maker;
    std::optional<std::string> maker_amount;
    std::optional<std::string> taker_amount;
    std::optional<common::Decimal> price;
    std::optional<std::string> quote_type;
    std::optional<std::string> created_at;
    std::optional<std::string> secret_token;

    bool operator==(const ListOtcBlocktradesResponseBlocktradesInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT ListOtcBlocktradesResponseBlocktradesInner
tag_invoke(boost::json::value_to_tag<ListOtcBlocktradesResponseBlocktradesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const ListOtcBlocktradesResponseBlocktradesInner& v);

} // namespace binance::w3w_prediction::rest_api
