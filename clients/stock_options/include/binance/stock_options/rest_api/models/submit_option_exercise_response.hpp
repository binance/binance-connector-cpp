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

struct SubmitOptionExerciseResponse {
    /// Exercise transaction ID; use it to query Option Exercise Detail.
    std::optional<std::int64_t> tran_id;
    /// Echoes the supplied or server-generated client ID.
    std::optional<std::string> client_order_id;
    /// `PROCESSING` on a first successful submission. When replayed with the same `clientOrderId`,
    /// the current status of the original exercise (`PROCESSING` / `SUCCESS`) is returned.
    std::optional<std::string> status;

    bool operator==(const SubmitOptionExerciseResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT SubmitOptionExerciseResponse tag_invoke(
    boost::json::value_to_tag<SubmitOptionExerciseResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const SubmitOptionExerciseResponse& v);

} // namespace binance::stock_options::rest_api
