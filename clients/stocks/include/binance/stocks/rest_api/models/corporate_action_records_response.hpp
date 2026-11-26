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

#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/corporate_action_records_response_items_inner.hpp>

namespace binance::stocks::rest_api {

struct CorporateActionRecordsResponse {
    /// Corporate action asset change records on this page.
    std::optional<std::vector<CorporateActionRecordsResponseItemsInner>> items;
    /// Pass this value as `lastTime` on the next request. Not returned on the last page.
    std::optional<std::int64_t> next_time;
    /// Pass this value as `lastId` on the next request. Not returned on the last page.
    std::optional<std::int64_t> next_id;

    bool operator==(const CorporateActionRecordsResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CorporateActionRecordsResponse
tag_invoke(boost::json::value_to_tag<CorporateActionRecordsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CorporateActionRecordsResponse& v);

} // namespace binance::stocks::rest_api
