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

struct MyAllocationsResponseInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> allocation_id;
    std::optional<std::string> allocation_type;
    std::optional<std::int64_t> order_id;
    std::optional<std::int64_t> order_list_id;
    std::optional<std::string> price;
    std::optional<std::string> qty;
    std::optional<std::string> quote_qty;
    std::optional<std::string> commission;
    std::optional<std::string> commission_asset;
    std::optional<std::int64_t> time;
    std::optional<bool> is_buyer;
    std::optional<bool> is_maker;
    std::optional<bool> is_allocator;

    bool operator==(const MyAllocationsResponseInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT MyAllocationsResponseInner tag_invoke(
    boost::json::value_to_tag<MyAllocationsResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const MyAllocationsResponseInner& v);

} // namespace binance::spot::rest_api
