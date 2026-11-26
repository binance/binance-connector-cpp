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
#include <binance/mining/rest_api/models/hashrate_resale_detail_response_data_profit_transfer_details_inner.hpp>

namespace binance::mining::rest_api {

struct HashrateResaleDetailResponseData {
    std::optional<std::vector<HashrateResaleDetailResponseDataProfitTransferDetailsInner>>
        profit_transfer_details;
    /// Total rows
    std::optional<std::int64_t> total_num;
    /// Rows per page
    std::optional<std::int64_t> page_size;

    bool operator==(const HashrateResaleDetailResponseData& /*other*/) const = default;
};

BINANCE_MINING_EXPORT HashrateResaleDetailResponseData
tag_invoke(boost::json::value_to_tag<HashrateResaleDetailResponseData> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const HashrateResaleDetailResponseData& v);

} // namespace binance::mining::rest_api
