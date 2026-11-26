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

struct AssetIndexResponse2Inner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> time;
    std::optional<std::string> index;
    std::optional<std::string> bid_buffer;
    std::optional<std::string> ask_buffer;
    std::optional<std::string> bid_rate;
    std::optional<std::string> ask_rate;
    std::optional<std::string> auto_exchange_bid_buffer;
    std::optional<std::string> auto_exchange_ask_buffer;
    std::optional<std::string> auto_exchange_bid_rate;
    std::optional<std::string> auto_exchange_ask_rate;

    bool operator==(const AssetIndexResponse2Inner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT AssetIndexResponse2Inner tag_invoke(
    boost::json::value_to_tag<AssetIndexResponse2Inner> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const AssetIndexResponse2Inner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
