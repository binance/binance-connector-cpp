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
#include <binance/mining/rest_api/models/hashrate_resale_list_response_data.hpp>

namespace binance::mining::rest_api {

struct HashrateResaleListResponse {
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;
    std::optional<HashrateResaleListResponseData> data;

    bool operator==(const HashrateResaleListResponse& /*other*/) const = default;
};

BINANCE_MINING_EXPORT HashrateResaleListResponse tag_invoke(
    boost::json::value_to_tag<HashrateResaleListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const HashrateResaleListResponse& v);

} // namespace binance::mining::rest_api
