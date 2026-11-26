//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/rebate/export.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response_data.hpp>

namespace binance::rebate::rest_api {

struct GetSpotRebateHistoryRecordsResponse {
    std::optional<std::string> status;
    std::optional<std::string> type;
    std::optional<std::string> code;
    std::optional<GetSpotRebateHistoryRecordsResponseData> data;

    bool operator==(const GetSpotRebateHistoryRecordsResponse& /*other*/) const = default;
};

BINANCE_REBATE_EXPORT GetSpotRebateHistoryRecordsResponse
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_REBATE_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetSpotRebateHistoryRecordsResponse& v);

} // namespace binance::rebate::rest_api
