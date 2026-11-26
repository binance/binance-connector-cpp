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
#include <binance/fiat/rest_api/models/deposit_response_data.hpp>

namespace binance::fiat::rest_api {

struct DepositResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<DepositResponseData> data;

    bool operator==(const DepositResponse& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT DepositResponse tag_invoke(boost::json::value_to_tag<DepositResponse> /*tag*/,
                                               const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const DepositResponse& v);

} // namespace binance::fiat::rest_api
