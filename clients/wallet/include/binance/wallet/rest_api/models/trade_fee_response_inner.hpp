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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct TradeFeeResponseInner {
    std::optional<std::string> symbol;
    std::optional<std::string> maker_commission;
    std::optional<std::string> taker_commission;

    bool operator==(const TradeFeeResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT TradeFeeResponseInner
tag_invoke(boost::json::value_to_tag<TradeFeeResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TradeFeeResponseInner& v);

} // namespace binance::wallet::rest_api
