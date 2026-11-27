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

struct CancelAlgoOrderResponse {
    std::optional<std::int64_t> algo_id;
    std::optional<std::string> client_algo_id;
    std::optional<std::string> code;
    std::optional<std::string> msg;

    bool operator==(const CancelAlgoOrderResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT CancelAlgoOrderResponse tag_invoke(
    boost::json::value_to_tag<CancelAlgoOrderResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const CancelAlgoOrderResponse& v);

} // namespace binance::derivatives_trading_coin_futures::rest_api
