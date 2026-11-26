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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct GetInterestHistoryResponseRowsInner {
    /// tx Id.
    std::optional<std::int64_t> tx_id;
    /// interest Accured Time.
    std::optional<std::int64_t> interest_accured_time;
    /// asset.
    std::optional<std::string> asset;
    /// will not be returned for isolated margin
    std::optional<std::string> raw_asset;
    /// principal.
    std::optional<std::string> principal;
    /// interest.
    std::optional<std::string> interest;
    /// interest Rate.
    std::optional<std::string> interest_rate;
    /// type.
    std::optional<std::string> type;
    /// isolated symbol, will not be returned for crossed margin
    std::optional<std::string> isolated_symbol;

    bool operator==(const GetInterestHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetInterestHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetInterestHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetInterestHistoryResponseRowsInner& v);

} // namespace binance::margin_trading::rest_api
