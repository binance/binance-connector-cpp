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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct OpenInterestResponseInner {
    /// symbol
    std::optional<std::string> symbol;
    /// sum Open Interest
    std::optional<std::string> sum_open_interest;
    /// sum Open Interest Usd
    std::optional<std::string> sum_open_interest_usd;
    /// timestamp
    std::optional<std::string> timestamp;

    bool operator==(const OpenInterestResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT OpenInterestResponseInner tag_invoke(
    boost::json::value_to_tag<OpenInterestResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           const OpenInterestResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
