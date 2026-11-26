//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

struct KlinesItemInner {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::int64_t, std::string, boost::json::value> value;

    bool operator==(const KlinesItemInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT KlinesItemInner tag_invoke(boost::json::value_to_tag<KlinesItemInner> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const KlinesItemInner& v);

} // namespace binance::spot::rest_api
