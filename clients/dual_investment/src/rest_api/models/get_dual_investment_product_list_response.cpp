//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/models/get_dual_investment_product_list_response.hpp>

namespace binance::dual_investment::rest_api {

GetDualInvestmentProductListResponse
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetDualInvestmentProductListResponse");
    GetDualInvestmentProductListResponse out;
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "list", out.list);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDualInvestmentProductListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "list", v.list);
}

} // namespace binance::dual_investment::rest_api
