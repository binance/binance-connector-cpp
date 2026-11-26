//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/statistic_list_response_data.hpp>

namespace binance::mining::rest_api {

StatisticListResponseData tag_invoke(boost::json::value_to_tag<StatisticListResponseData> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StatisticListResponseData");
    StatisticListResponseData out;
    common::detail::json::read(obj, "fifteenMinHashRate", out.fifteen_min_hash_rate);
    common::detail::json::read(obj, "dayHashRate", out.day_hash_rate);
    common::detail::json::read(obj, "validNum", out.valid_num);
    common::detail::json::read(obj, "invalidNum", out.invalid_num);
    common::detail::json::read(obj, "profitToday", out.profit_today);
    common::detail::json::read(obj, "profitYesterday", out.profit_yesterday);
    common::detail::json::read(obj, "userName", out.user_name);
    common::detail::json::read(obj, "unit", out.unit);
    common::detail::json::read(obj, "algo", out.algo);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StatisticListResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "fifteenMinHashRate", v.fifteen_min_hash_rate);
    common::detail::json::write(obj, "dayHashRate", v.day_hash_rate);
    common::detail::json::write(obj, "validNum", v.valid_num);
    common::detail::json::write(obj, "invalidNum", v.invalid_num);
    common::detail::json::write(obj, "profitToday", v.profit_today);
    common::detail::json::write(obj, "profitYesterday", v.profit_yesterday);
    common::detail::json::write(obj, "userName", v.user_name);
    common::detail::json::write(obj, "unit", v.unit);
    common::detail::json::write(obj, "algo", v.algo);
}

} // namespace binance::mining::rest_api
