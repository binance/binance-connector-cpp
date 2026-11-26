//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/simple_earn/export.hpp>

namespace binance::simple_earn::rest_api {

struct GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate {
    std::optional<common::Decimal> r_0_5_btc;
    std::optional<common::Decimal> r_5_10_btc;

    bool
    operator==(const GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate& /*other*/)
        const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate
tag_invoke(boost::json::value_to_tag<
               GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate> /*tag*/,
           const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleProductPositionResponseRowsInnerTierAnnualPercentageRate& v);

} // namespace binance::simple_earn::rest_api
