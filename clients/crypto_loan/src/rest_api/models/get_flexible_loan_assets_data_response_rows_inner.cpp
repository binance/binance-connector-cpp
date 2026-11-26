//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/crypto_loan/rest_api/models/get_flexible_loan_assets_data_response_rows_inner.hpp>

namespace binance::crypto_loan::rest_api {

GetFlexibleLoanAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetFlexibleLoanAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetFlexibleLoanAssetsDataResponseRowsInner");
    GetFlexibleLoanAssetsDataResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "flexibleInterestRate", out.flexible_interest_rate);
    common::detail::json::read(obj, "flexibleMinLimit", out.flexible_min_limit);
    common::detail::json::read(obj, "flexibleMaxLimit", out.flexible_max_limit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFlexibleLoanAssetsDataResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "flexibleInterestRate", v.flexible_interest_rate);
    common::detail::json::write(obj, "flexibleMinLimit", v.flexible_min_limit);
    common::detail::json::write(obj, "flexibleMaxLimit", v.flexible_max_limit);
}

} // namespace binance::crypto_loan::rest_api
