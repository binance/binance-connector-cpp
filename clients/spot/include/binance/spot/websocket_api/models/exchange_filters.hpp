//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/exchange_max_num_algo_orders_filter.hpp>
#include <binance/spot/websocket_api/models/exchange_max_num_iceberg_orders_filter.hpp>
#include <binance/spot/websocket_api/models/exchange_max_num_order_lists_filter.hpp>
#include <binance/spot/websocket_api/models/exchange_max_num_orders_filter.hpp>

namespace binance::spot::websocket_api {

struct ExchangeFilters {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<ExchangeMaxNumOrdersFilter, ExchangeMaxNumAlgoOrdersFilter,
                 ExchangeMaxNumIcebergOrdersFilter, ExchangeMaxNumOrderListsFilter,
                 boost::json::value>
        value;

    bool operator==(const ExchangeFilters& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeFilters tag_invoke(boost::json::value_to_tag<ExchangeFilters> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeFilters& v);

} // namespace binance::spot::websocket_api
