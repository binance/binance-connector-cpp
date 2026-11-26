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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionExerciseDetailResponse {
    /// Exercise transaction ID.
    std::optional<std::int64_t> tran_id;
    /// Client ID.
    std::optional<std::string> client_order_id;
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// OCC root symbol. Differs from `underlyingSymbol` for contracts adjusted by a corporate
    /// action (e.g. `GOOG1`).
    std::optional<std::string> root_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Requested number of contracts.
    std::optional<std::string> requested_qty;
    /// `PROCESSING` / `SUCCESS` / `FAILED`.
    std::optional<std::string> status;
    /// Submission time (ms).
    std::optional<std::int64_t> requested_time;
    /// Last update time (ms).
    std::optional<std::int64_t> update_time;
    /// Settlement event ID of the option leg; can be used with Option Settlement Event Detail.
    std::optional<std::string> option_event_id;
    /// Settlement event ID of the underlying-share leg.
    std::optional<std::string> underlying_event_id;
    /// Premium multiplier. Order cost = price × quantity × multiplier.
    std::optional<std::string> multiplier;
    /// Error code on failure; one of the option business error codes in Error Code. Returned only
    /// when `status` is `FAILED`.
    std::optional<std::string> error_code;

    bool operator==(const OptionExerciseDetailResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionExerciseDetailResponse tag_invoke(
    boost::json::value_to_tag<OptionExerciseDetailResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionExerciseDetailResponse& v);

} // namespace binance::stock_options::rest_api
