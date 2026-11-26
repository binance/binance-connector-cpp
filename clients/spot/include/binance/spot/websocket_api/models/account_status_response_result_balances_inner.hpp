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

#include <binance/spot/export.hpp>

namespace binance::spot::websocket_api {

struct AccountStatusResponseResultBalancesInner {
    std::optional<std::string> asset;
    std::optional<std::string> free;
    std::optional<std::string> locked;

    bool operator==(const AccountStatusResponseResultBalancesInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountStatusResponseResultBalancesInner
tag_invoke(boost::json::value_to_tag<AccountStatusResponseResultBalancesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountStatusResponseResultBalancesInner& v);

} // namespace binance::spot::websocket_api
