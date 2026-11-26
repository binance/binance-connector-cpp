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

struct GetFlexibleLoanCollateralAssetsDataResponseRowsInner {
    std::optional<std::string> collateral_coin;
    std::optional<std::string> initial_ltv;
    std::optional<std::string> margin_call_ltv;
    std::optional<std::string> liquidation_ltv;
    std::optional<std::string> max_limit;

    bool operator==(const GetFlexibleLoanCollateralAssetsDataResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanCollateralAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanCollateralAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetFlexibleLoanCollateralAssetsDataResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
