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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

struct GetExchangeInfoResponseDataAssetsInner {
    /// Asset symbol.
    std::optional<std::string> asset;

    bool operator==(const GetExchangeInfoResponseDataAssetsInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT GetExchangeInfoResponseDataAssetsInner
tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponseDataAssetsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const GetExchangeInfoResponseDataAssetsInner& v);

} // namespace binance::alpha::rest_api
