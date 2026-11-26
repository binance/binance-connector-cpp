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

#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/request_for_miner_list_response_data_worker_datas_inner.hpp>

namespace binance::mining::rest_api {

struct RequestForMinerListResponseData {
    std::optional<std::vector<RequestForMinerListResponseDataWorkerDatasInner>> worker_datas;
    /// Total amount
    std::optional<std::int64_t> total_num;
    /// Rows per page
    std::optional<std::int64_t> page_size;

    bool operator==(const RequestForMinerListResponseData& /*other*/) const = default;
};

BINANCE_MINING_EXPORT RequestForMinerListResponseData
tag_invoke(boost::json::value_to_tag<RequestForMinerListResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const RequestForMinerListResponseData& v);

} // namespace binance::mining::rest_api
