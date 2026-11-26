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

#include <binance/crypto_loan/export.hpp>

namespace binance::crypto_loan::rest_api {

struct CheckCollateralRepayRateResponse {
    std::optional<std::string> loan_coin;
    std::optional<std::string> collateral_coin;
    /// rate of collateral coin/loan coin
    std::optional<std::string> rate;

    bool operator==(const CheckCollateralRepayRateResponse& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT CheckCollateralRepayRateResponse
tag_invoke(boost::json::value_to_tag<CheckCollateralRepayRateResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const CheckCollateralRepayRateResponse& v);

} // namespace binance::crypto_loan::rest_api
