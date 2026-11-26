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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AdlRiskResponse2Inner {
    std::optional<std::string> symbol;
    /// ADL Risk rating
    std::optional<std::string> adl_risk;
    std::optional<std::int64_t> update_time;

    bool operator==(const AdlRiskResponse2Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AdlRiskResponse2Inner
tag_invoke(boost::json::value_to_tag<AdlRiskResponse2Inner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AdlRiskResponse2Inner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
