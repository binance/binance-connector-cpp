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
#include <binance/spot/rest_api/models/iceberg_parts_filter.hpp>
#include <binance/spot/rest_api/models/lot_size_filter.hpp>
#include <binance/spot/rest_api/models/market_lot_size_filter.hpp>
#include <binance/spot/rest_api/models/max_num_algo_orders_filter.hpp>
#include <binance/spot/rest_api/models/max_num_iceberg_orders_filter.hpp>
#include <binance/spot/rest_api/models/max_num_order_amends_filter.hpp>
#include <binance/spot/rest_api/models/max_num_order_lists_filter.hpp>
#include <binance/spot/rest_api/models/max_num_orders_filter.hpp>
#include <binance/spot/rest_api/models/max_position_filter.hpp>
#include <binance/spot/rest_api/models/min_notional_filter.hpp>
#include <binance/spot/rest_api/models/notional_filter.hpp>
#include <binance/spot/rest_api/models/percent_price_by_side_filter.hpp>
#include <binance/spot/rest_api/models/percent_price_filter.hpp>
#include <binance/spot/rest_api/models/price_filter.hpp>
#include <binance/spot/rest_api/models/t_plus_sell_filter.hpp>
#include <binance/spot/rest_api/models/trailing_delta_filter.hpp>

namespace binance::spot::rest_api {

struct SymbolFilters {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<PriceFilter, PercentPriceFilter, PercentPriceBySideFilter, LotSizeFilter,
                 MinNotionalFilter, NotionalFilter, IcebergPartsFilter, MarketLotSizeFilter,
                 MaxNumOrdersFilter, MaxNumAlgoOrdersFilter, MaxNumIcebergOrdersFilter,
                 MaxPositionFilter, TrailingDeltaFilter, TPlusSellFilter, MaxNumOrderListsFilter,
                 MaxNumOrderAmendsFilter, boost::json::value>
        value;

    bool operator==(const SymbolFilters& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT SymbolFilters tag_invoke(boost::json::value_to_tag<SymbolFilters> /*tag*/,
                                             const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const SymbolFilters& v);

} // namespace binance::spot::rest_api
