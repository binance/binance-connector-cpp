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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/avg_price_response_rate_limits_inner.hpp>
#include <binance/spot/websocket_api/models/klines_response_result_inner_inner.hpp>

namespace binance::spot::websocket_api {

struct UiKlinesResponse {
    std::optional<std::string> id;
    std::optional<std::int64_t> status;
    std::optional<std::vector<std::vector<KlinesResponseResultInnerInner>>> result;
    std::optional<std::vector<AvgPriceResponseRateLimitsInner>> rate_limits;

    bool operator==(const UiKlinesResponse& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT UiKlinesResponse tag_invoke(boost::json::value_to_tag<UiKlinesResponse> /*tag*/,
                                                const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const UiKlinesResponse& v);

} // namespace binance::spot::websocket_api
