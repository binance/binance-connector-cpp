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

struct FiatWithdrawResponseData {
    std::optional<std::string> order_id;

    bool operator==(const FiatWithdrawResponseData& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT FiatWithdrawResponseData tag_invoke(
    boost::json::value_to_tag<FiatWithdrawResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const FiatWithdrawResponseData& v);

} // namespace binance::fiat::rest_api
