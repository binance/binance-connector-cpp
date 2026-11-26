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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response_regions_inner.hpp>

namespace binance::wallet::rest_api {

struct GetRegionListResponse {
    /// Echoed country code (lowercase).
    std::optional<std::string> country_code;
    std::optional<std::vector<GetRegionListResponseRegionsInner>> regions;
    /// Last data update timestamp (epoch milliseconds); 0 if empty.
    std::optional<std::int64_t> last_updated;

    bool operator==(const GetRegionListResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetRegionListResponse
tag_invoke(boost::json::value_to_tag<GetRegionListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetRegionListResponse& v);

} // namespace binance::wallet::rest_api
