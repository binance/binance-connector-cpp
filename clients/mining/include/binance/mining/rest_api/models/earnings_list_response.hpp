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

#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/earnings_list_response_data.hpp>

namespace binance::mining::rest_api {

struct EarningsListResponse {
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;
    std::optional<EarningsListResponseData> data;

    bool operator==(const EarningsListResponse& /*other*/) const = default;
};

BINANCE_MINING_EXPORT EarningsListResponse
tag_invoke(boost::json::value_to_tag<EarningsListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const EarningsListResponse& v);

} // namespace binance::mining::rest_api
