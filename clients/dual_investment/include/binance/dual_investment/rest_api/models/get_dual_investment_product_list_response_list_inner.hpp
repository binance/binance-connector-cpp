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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/dual_investment/export.hpp>

namespace binance::dual_investment::rest_api {

struct GetDualInvestmentProductListResponseListInner {
    std::optional<std::string> id;
    std::optional<std::string> invest_coin;
    std::optional<std::string> exercised_coin;
    std::optional<std::string> strike_price;
    std::optional<std::int64_t> duration;
    std::optional<std::int64_t> settle_date;
    std::optional<std::int64_t> purchase_decimal;
    std::optional<std::int64_t> purchase_end_time;
    /// Whether the product can be subscribed to currently
    std::optional<bool> can_purchase;
    std::optional<std::string> apr;
    std::optional<std::int64_t> order_id;
    std::optional<std::string> min_amount;
    std::optional<std::string> max_amount;
    std::optional<std::int64_t> create_timestamp;
    std::optional<std::string> option_type;
    /// Whether auto-compound is enabled for this product
    std::optional<bool> is_auto_compound_enable;
    /// Available auto-compound plans for this product
    std::optional<std::vector<std::string>> auto_compound_plan_list;

    bool operator==(const GetDualInvestmentProductListResponseListInner& /*other*/) const = default;
};

BINANCE_DUAL_INVESTMENT_EXPORT GetDualInvestmentProductListResponseListInner
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListResponseListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetDualInvestmentProductListResponseListInner& v);

} // namespace binance::dual_investment::rest_api
