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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/crypto_loan/export.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_assets_data_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

struct GetFlexibleLoanAssetsDataResponse {
    std::optional<std::vector<GetFlexibleLoanAssetsDataResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const GetFlexibleLoanAssetsDataResponse& /*other*/) const = default;
};

BINANCE_CRYPTO_LOAN_EXPORT GetFlexibleLoanAssetsDataResponse
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanAssetsDataResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_CRYPTO_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetFlexibleLoanAssetsDataResponse& v);

} // namespace binance::crypto_loan::rest_api
