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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/rebate/export.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response_data_data_inner.hpp>

namespace binance::rebate::rest_api {

struct GetSpotRebateHistoryRecordsResponseData {
    /// Current page number.
    std::optional<std::int64_t> page;
    /// Total number of records.
    std::optional<std::int64_t> total_records;
    /// Total number of pages.
    std::optional<std::int64_t> total_page_num;
    /// Rebate records.
    std::optional<std::vector<GetSpotRebateHistoryRecordsResponseDataDataInner>> data;

    bool operator==(const GetSpotRebateHistoryRecordsResponseData& /*other*/) const = default;
};

BINANCE_REBATE_EXPORT GetSpotRebateHistoryRecordsResponseData
tag_invoke(boost::json::value_to_tag<GetSpotRebateHistoryRecordsResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_REBATE_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetSpotRebateHistoryRecordsResponseData& v);

} // namespace binance::rebate::rest_api
