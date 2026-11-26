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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct ToggleBnbBurnOnSpotTradeAndMarginInterestResponse {
    std::optional<bool> spot_bnb_burn;
    std::optional<bool> interest_bnb_burn;

    bool
    operator==(const ToggleBnbBurnOnSpotTradeAndMarginInterestResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT ToggleBnbBurnOnSpotTradeAndMarginInterestResponse
tag_invoke(boost::json::value_to_tag<ToggleBnbBurnOnSpotTradeAndMarginInterestResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const ToggleBnbBurnOnSpotTradeAndMarginInterestResponse& v);

} // namespace binance::wallet::rest_api
