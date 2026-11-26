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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct ExchangeInfoResponseSorsInner {
    std::optional<std::string> base_asset;
    std::optional<std::vector<std::string>> symbols;

    bool operator==(const ExchangeInfoResponseSorsInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeInfoResponseSorsInner tag_invoke(
    boost::json::value_to_tag<ExchangeInfoResponseSorsInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeInfoResponseSorsInner& v);

} // namespace binance::spot::websocket_api
