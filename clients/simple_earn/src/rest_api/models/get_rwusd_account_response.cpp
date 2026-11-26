//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_account_response.hpp>

namespace binance::simple_earn::rest_api {

GetRwusdAccountResponse tag_invoke(boost::json::value_to_tag<GetRwusdAccountResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetRwusdAccountResponse");
    GetRwusdAccountResponse out;
    common::detail::json::read(obj, "rwusdAmount", out.rwusd_amount);
    common::detail::json::read(obj, "totalProfit", out.total_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetRwusdAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "rwusdAmount", v.rwusd_amount);
    common::detail::json::write(obj, "totalProfit", v.total_profit);
}

} // namespace binance::simple_earn::rest_api
