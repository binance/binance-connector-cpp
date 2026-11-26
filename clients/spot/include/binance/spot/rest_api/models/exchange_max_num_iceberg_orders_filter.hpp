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

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct ExchangeMaxNumIcebergOrdersFilter {
    std::optional<std::string> filter_type;
    std::optional<std::int64_t> max_num_iceberg_orders;

    bool operator==(const ExchangeMaxNumIcebergOrdersFilter& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeMaxNumIcebergOrdersFilter
tag_invoke(boost::json::value_to_tag<ExchangeMaxNumIcebergOrdersFilter> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeMaxNumIcebergOrdersFilter& v);

} // namespace binance::spot::rest_api
