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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/request_for_detail_miner_list_response_data_inner_hashrate_datas_inner.hpp>

namespace binance::mining::rest_api {

struct RequestForDetailMinerListResponseDataInner {
    /// Mining account name
    std::optional<std::string> worker_name;
    /// Type of hashrate bucket
    std::optional<std::string> type;
    std::optional<std::vector<RequestForDetailMinerListResponseDataInnerHashrateDatasInner>>
        hashrate_datas;

    bool operator==(const RequestForDetailMinerListResponseDataInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT RequestForDetailMinerListResponseDataInner
tag_invoke(boost::json::value_to_tag<RequestForDetailMinerListResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const RequestForDetailMinerListResponseDataInner& v);

} // namespace binance::mining::rest_api
