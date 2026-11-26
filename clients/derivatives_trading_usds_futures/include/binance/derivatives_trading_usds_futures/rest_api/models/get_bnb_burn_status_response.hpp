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

#include <binance/derivatives_trading_usds_futures/export.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct GetBnbBurnStatusResponse {
    /// "true": Fee Discount On; "false": Fee Discount Off
    std::optional<bool> fee_burn;

    bool operator==(const GetBnbBurnStatusResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT GetBnbBurnStatusResponse tag_invoke(
    boost::json::value_to_tag<GetBnbBurnStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                const GetBnbBurnStatusResponse& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
