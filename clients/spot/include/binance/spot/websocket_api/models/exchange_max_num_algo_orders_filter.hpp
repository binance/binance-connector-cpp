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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct ExchangeMaxNumAlgoOrdersFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> max_num_algo_orders;

    bool operator==(const ExchangeMaxNumAlgoOrdersFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeMaxNumAlgoOrdersFilter
tag_invoke(boost::json::value_to_tag<ExchangeMaxNumAlgoOrdersFilter> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeMaxNumAlgoOrdersFilter& v);

} // namespace binance::spot::websocket_api
