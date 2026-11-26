//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_loanable_assets_data_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetLoanableAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLoanableAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetLoanableAssetsDataResponseRowsInner");
    GetLoanableAssetsDataResponseRowsInner out;
    common::detail::json::read(obj, "loanCoin", out.loan_coin);
    common::detail::json::read(obj, "_flexibleDailyInterestRate",
                               out._flexible_daily_interest_rate);
    common::detail::json::read(obj, "_flexibleYearlyInterestRate",
                               out._flexible_yearly_interest_rate);
    common::detail::json::read(obj, "_30dDailyInterestRate", out._30d_daily_interest_rate);
    common::detail::json::read(obj, "_30dYearlyInterestRate", out._30d_yearly_interest_rate);
    common::detail::json::read(obj, "_60dDailyInterestRate", out._60d_daily_interest_rate);
    common::detail::json::read(obj, "_60dYearlyInterestRate", out._60d_yearly_interest_rate);
    common::detail::json::read(obj, "minLimit", out.min_limit);
    common::detail::json::read(obj, "maxLimit", out.max_limit);
    common::detail::json::read(obj, "vipLevel", out.vip_level);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetLoanableAssetsDataResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "loanCoin", v.loan_coin);
    common::detail::json::write(obj, "_flexibleDailyInterestRate", v._flexible_daily_interest_rate);
    common::detail::json::write(obj, "_flexibleYearlyInterestRate",
                                v._flexible_yearly_interest_rate);
    common::detail::json::write(obj, "_30dDailyInterestRate", v._30d_daily_interest_rate);
    common::detail::json::write(obj, "_30dYearlyInterestRate", v._30d_yearly_interest_rate);
    common::detail::json::write(obj, "_60dDailyInterestRate", v._60d_daily_interest_rate);
    common::detail::json::write(obj, "_60dYearlyInterestRate", v._60d_yearly_interest_rate);
    common::detail::json::write(obj, "minLimit", v.min_limit);
    common::detail::json::write(obj, "maxLimit", v.max_limit);
    common::detail::json::write(obj, "vipLevel", v.vip_level);
}

} // namespace binance::vip_loan::rest_api
