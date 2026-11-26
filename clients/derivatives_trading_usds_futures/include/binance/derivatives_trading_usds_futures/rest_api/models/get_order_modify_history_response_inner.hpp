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
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_order_modify_history_response_inner_amendment.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetOrderModifyHistoryResponseInner {
    /// Order modification ID
    std::optional<std::int64_t> amendment_id;
    std::optional<std::string> symbol;
    std::optional<std::string> pair;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> client_order_id;
    /// Order modification time
    std::optional<std::int64_t> time;
    std::optional<GetOrderModifyHistoryResponseInnerAmendment> amendment;

    bool operator==(const GetOrderModifyHistoryResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetOrderModifyHistoryResponseInner
tag_invoke(boost::json::value_to_tag<GetOrderModifyHistoryResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetOrderModifyHistoryResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
