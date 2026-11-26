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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct QuarterlyContractSettlementPriceResponseInner {
    std::optional<std::int64_t> delivery_time;
    std::optional<common::Decimal> delivery_price;

    bool operator==(const QuarterlyContractSettlementPriceResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT QuarterlyContractSettlementPriceResponseInner
tag_invoke(boost::json::value_to_tag<QuarterlyContractSettlementPriceResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QuarterlyContractSettlementPriceResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
