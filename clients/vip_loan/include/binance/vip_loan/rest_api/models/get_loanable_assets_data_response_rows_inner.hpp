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
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/vip_loan/export.hpp>

namespace binance::vip_loan::rest_api {

struct GetLoanableAssetsDataResponseRowsInner {
    std::optional<std::string> loan_coin;
    std::optional<std::string> _flexible_daily_interest_rate;
    std::optional<std::string> _flexible_yearly_interest_rate;
    std::optional<std::string> _30d_daily_interest_rate;
    std::optional<std::string> _30d_yearly_interest_rate;
    std::optional<std::string> _60d_daily_interest_rate;
    std::optional<std::string> _60d_yearly_interest_rate;
    std::optional<std::string> min_limit;
    std::optional<std::string> max_limit;
    std::optional<std::int64_t> vip_level;

    bool operator==(const GetLoanableAssetsDataResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetLoanableAssetsDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetLoanableAssetsDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetLoanableAssetsDataResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
