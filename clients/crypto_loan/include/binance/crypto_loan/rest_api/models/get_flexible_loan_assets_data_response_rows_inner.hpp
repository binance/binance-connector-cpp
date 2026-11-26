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

struct GetFlexibleLoanAssetsDataResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> flexible_interest_rate;
    std::optional<std::string> flexible_min_limit;
    std::optional<std::string> flexible_max_limit;

    bool operator==(const GetFlexibleLoanAssetsDataResponseRowsInner& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleLoanAssetsDataResponseRowsInner& v);

} // namespace binance::crypto_loan::rest_api
