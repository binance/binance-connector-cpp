//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_account_response.hpp>

namespace binance::simple_earn::rest_api {

GetBfusdAccountResponse tag_invoke(boost::json::value_to_tag<GetBfusdAccountResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetBfusdAccountResponse");
    GetBfusdAccountResponse out;
    common::detail::json::read(obj, "bfusdAmount", out.bfusd_amount);
    common::detail::json::read(obj, "usdtProfit", out.usdt_profit);
    common::detail::json::read(obj, "bfusdProfit", out.bfusd_profit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetBfusdAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bfusdAmount", v.bfusd_amount);
    common::detail::json::write(obj, "usdtProfit", v.usdt_profit);
    common::detail::json::write(obj, "bfusdProfit", v.bfusd_profit);
}

} // namespace binance::simple_earn::rest_api
