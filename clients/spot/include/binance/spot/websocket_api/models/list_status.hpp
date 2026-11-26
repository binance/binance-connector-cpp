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

#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/list_status_o_inner.hpp>

namespace binance::spot::websocket_api {

struct ListStatus {
    /// Event Time
    std::optional<std::int64_t> e_uppercase;
    /// Symbol
    std::optional<std::string> s;
    /// OrderListId
    std::optional<std::int64_t> g;
    /// Contingency Type
    std::optional<std::string> c;
    /// List Status Type
    std::optional<std::string> l;
    /// List Order Status
    std::optional<std::string> l_uppercase;
    /// List Reject Reason
    std::optional<std::string> r;
    /// List Client Order ID
    std::optional<std::string> c_uppercase;
    /// Transaction Time
    std::optional<std::int64_t> t_uppercase;
    /// An array of objects
    std::optional<std::vector<ListStatusOInner>> o_uppercase;

    bool operator==(const ListStatus& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ListStatus tag_invoke(boost::json::value_to_tag<ListStatus> /*tag*/,
                                          const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ListStatus& v);

} // namespace binance::spot::websocket_api
