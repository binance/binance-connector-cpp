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

struct ExchangeInformationResponseOptionContractsInner {
    /// Base currency
    std::optional<std::string> base_asset;
    /// Quotation asset
    std::optional<std::string> quote_asset;
    /// Name of the underlying asset of the option contract
    std::optional<std::string> underlying;
    /// Settlement currency
    std::optional<std::string> settle_asset;

    bool
    operator==(const ExchangeInformationResponseOptionContractsInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT ExchangeInformationResponseOptionContractsInner
tag_invoke(boost::json::value_to_tag<ExchangeInformationResponseOptionContractsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const ExchangeInformationResponseOptionContractsInner& v);

} // namespace binance::derivatives_trading_options::rest_api
