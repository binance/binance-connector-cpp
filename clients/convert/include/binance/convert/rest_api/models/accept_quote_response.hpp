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

#include <binance/convert/export.hpp>

namespace binance::convert::rest_api {

struct AcceptQuoteResponse {
    std::optional<std::string> order_id;
    std::optional<std::int64_t> create_time;
    /// Order processing status
    std::optional<std::string> order_status;

    bool operator==(const AcceptQuoteResponse& /*other*/) const = default;
};

BINANCE_CONVERT_EXPORT AcceptQuoteResponse
tag_invoke(boost::json::value_to_tag<AcceptQuoteResponse> /*tag*/, const boost::json::value& jv);
BINANCE_CONVERT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const AcceptQuoteResponse& v);

} // namespace binance::convert::rest_api
