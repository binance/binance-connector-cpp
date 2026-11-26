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

#include <binance/mining/export.hpp>

namespace binance::mining::rest_api {

struct CancelHashrateResaleConfigurationResponse {
    std::optional<std::int64_t> code;
    std::optional<std::string> msg;
    std::optional<bool> data;

    bool operator==(const CancelHashrateResaleConfigurationResponse& /*other*/) const = default;
};

BINANCE_MINING_EXPORT CancelHashrateResaleConfigurationResponse
tag_invoke(boost::json::value_to_tag<CancelHashrateResaleConfigurationResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CancelHashrateResaleConfigurationResponse& v);

} // namespace binance::mining::rest_api
