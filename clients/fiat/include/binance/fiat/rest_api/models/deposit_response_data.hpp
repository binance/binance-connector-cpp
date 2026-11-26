//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/fiat/export.hpp>

namespace binance::fiat::rest_api {

struct DepositResponseData {
    /// deposit order id
    std::optional<std::string> order_id;

    bool operator==(const DepositResponseData& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT DepositResponseData
tag_invoke(boost::json::value_to_tag<DepositResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const DepositResponseData& v);

} // namespace binance::fiat::rest_api
