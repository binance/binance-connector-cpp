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

#include <binance/dual_investment/export.hpp>
#include <binance/dual_investment/rest_api/models/get_dual_investment_product_list_response_list_inner.hpp>

namespace binance::dual_investment::rest_api {

struct GetDualInvestmentProductListResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<GetDualInvestmentProductListResponseListInner>> list;

    bool operator==(const GetDualInvestmentProductListResponse& /*other*/) const = default;
};

BINANCE_DUAL_INVESTMENT_EXPORT GetDualInvestmentProductListResponse
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                               boost::json::value& jv,
                                               const GetDualInvestmentProductListResponse& v);

} // namespace binance::dual_investment::rest_api
