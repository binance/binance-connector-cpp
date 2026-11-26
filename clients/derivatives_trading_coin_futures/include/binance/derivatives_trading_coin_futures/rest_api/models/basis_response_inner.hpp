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

#include <binance/derivatives_trading_coin_futures/export.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

struct BasisResponseInner {
    /// index price
    std::optional<std::string> index_price;
    /// Contract type.
    std::optional<std::string> contract_type;
    /// Basis rate.
    std::optional<std::string> basis_rate;
    /// Futures price.
    std::optional<std::string> futures_price;
    /// Annualized basis rate.
    std::optional<std::string> annualized_basis_rate;
    /// Basis value.
    std::optional<std::string> basis;
    /// Pair
    std::optional<std::string> pair;
    /// Start time of the period, in milliseconds.
    std::optional<std::int64_t> timestamp;

    bool operator==(const BasisResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT BasisResponseInner
tag_invoke(boost::json::value_to_tag<BasisResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const BasisResponseInner& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
