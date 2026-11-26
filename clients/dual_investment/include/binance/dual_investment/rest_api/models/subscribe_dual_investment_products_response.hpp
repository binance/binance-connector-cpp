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

#include <binance/dual_investment/export.hpp>

namespace binance::dual_investment::rest_api {

struct SubscribeDualInvestmentProductsResponse {
    std::optional<std::int64_t> position_id;
    std::optional<std::string> invest_coin;
    std::optional<std::string> exercised_coin;
    std::optional<std::string> subscription_amount;
    std::optional<std::int64_t> duration;
    /// STANDARD, ADVANCED, this field won't display when autocompound is set to None
    std::optional<std::string> auto_compound_plan;
    std::optional<std::string> strike_price;
    std::optional<std::int64_t> settle_date;
    std::optional<std::string> purchase_status;
    std::optional<std::string> apr;
    std::optional<std::int64_t> order_id;
    std::optional<std::int64_t> purchase_time;
    std::optional<std::string> option_type;

    bool operator==(const SubscribeDualInvestmentProductsResponse& /*other*/) const = default;
};

BINANCE_DUAL_INVESTMENT_EXPORT SubscribeDualInvestmentProductsResponse
tag_invoke(boost::json::value_to_tag<SubscribeDualInvestmentProductsResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                               boost::json::value& jv,
                                               const SubscribeDualInvestmentProductsResponse& v);

} // namespace binance::dual_investment::rest_api
