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

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

struct KlinesResponseDataInnerInner {
    /// One of the alternatives, or the raw JSON when none matches.
    std::variant<std::string, std::int64_t, boost::json::value> value;

    bool operator==(const KlinesResponseDataInnerInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT KlinesResponseDataInnerInner tag_invoke(
    boost::json::value_to_tag<KlinesResponseDataInnerInner> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const KlinesResponseDataInnerInner& v);

} // namespace binance::alpha::rest_api
