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

struct BasisResponseInner {
    std::optional<std::string> index_price;
    std::optional<std::string> contract_type;
    std::optional<std::string> basis_rate;
    std::optional<std::string> futures_price;
    std::optional<std::string> annualized_basis_rate;
    std::optional<std::string> basis;
    std::optional<std::string> pair;
    /// Start time of the period, in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const BasisResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT BasisResponseInner
tag_invoke(boost::json::value_to_tag<BasisResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const BasisResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
