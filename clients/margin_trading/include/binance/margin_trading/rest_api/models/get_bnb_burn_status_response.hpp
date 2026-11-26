//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct GetBnbBurnStatusResponse {
    /// spot BNBBurn.
    std::optional<bool> spot_bnb_burn;
    /// interest BNBBurn.
    std::optional<bool> interest_bnb_burn;

    bool operator==(const GetBnbBurnStatusResponse& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetBnbBurnStatusResponse tag_invoke(
    boost::json::value_to_tag<GetBnbBurnStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetBnbBurnStatusResponse& v);

} // namespace binance::margin_trading::rest_api
