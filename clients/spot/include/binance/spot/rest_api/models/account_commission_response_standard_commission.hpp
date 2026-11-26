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

#include <binance/spot/export.hpp>

namespace binance::spot::rest_api {

/// Commission rates on trades from the order.
struct AccountCommissionResponseStandardCommission {
    std::optional<std::string> maker;
    std::optional<std::string> taker;
    std::optional<std::string> buyer;
    std::optional<std::string> seller;

    bool operator==(const AccountCommissionResponseStandardCommission& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT AccountCommissionResponseStandardCommission
tag_invoke(boost::json::value_to_tag<AccountCommissionResponseStandardCommission> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const AccountCommissionResponseStandardCommission& v);

} // namespace binance::spot::rest_api
