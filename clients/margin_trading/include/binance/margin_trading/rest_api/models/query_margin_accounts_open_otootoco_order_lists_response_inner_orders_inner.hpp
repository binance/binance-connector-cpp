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

struct QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner {
    /// symbol.
    std::optional<std::string> symbol;
    /// order Id. Returns `null` if the working order is not filled yet.
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::int64_t>> order_id;
    /// status.
    std::optional<std::string> status;
    /// client Order Id.
    std::optional<std::string> client_order_id;

    bool
    operator==(const QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner& /*other*/)
        const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner
tag_invoke(boost::json::value_to_tag<
               QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner& v);

} // namespace binance::margin_trading::rest_api
