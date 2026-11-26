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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/query_margin_accounts_open_otootoco_order_lists_response_inner_orders_inner.hpp>

namespace binance::margin_trading::rest_api {

struct QueryMarginAccountsOpenOtootocoOrderListsResponseInner {
    /// order List Id.
    std::optional<std::int64_t> order_list_id;
    /// contingency Type.
    std::optional<std::string> contingency_type;
    /// list Status Type.
    std::optional<std::string> list_status_type;
    /// list Order Status.
    std::optional<std::string> list_order_status;
    /// list Client Order Id.
    std::optional<std::string> list_client_order_id;
    /// transaction Time.
    std::optional<std::int64_t> transaction_time;
    /// symbol.
    std::optional<std::string> symbol;
    /// orders list.
    std::optional<std::vector<QueryMarginAccountsOpenOtootocoOrderListsResponseInnerOrdersInner>>
        orders;

    bool operator==(const QueryMarginAccountsOpenOtootocoOrderListsResponseInner& /*other*/) const =
        default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsOpenOtootocoOrderListsResponseInner tag_invoke(
    boost::json::value_to_tag<QueryMarginAccountsOpenOtootocoOrderListsResponseInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryMarginAccountsOpenOtootocoOrderListsResponseInner& v);

} // namespace binance::margin_trading::rest_api
