//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/simple_earn/rest_api/models/simple_account_response.hpp>

namespace binance::simple_earn::rest_api {

SimpleAccountResponse tag_invoke(boost::json::value_to_tag<SimpleAccountResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SimpleAccountResponse");
    SimpleAccountResponse out;
    common::detail::json::read(obj, "totalAmountInBTC", out.total_amount_in_btc);
    common::detail::json::read(obj, "totalAmountInUSDT", out.total_amount_in_usdt);
    common::detail::json::read(obj, "totalFlexibleAmountInBTC", out.total_flexible_amount_in_btc);
    common::detail::json::read(obj, "totalFlexibleAmountInUSDT", out.total_flexible_amount_in_usdt);
    common::detail::json::read(obj, "totalLockedInBTC", out.total_locked_in_btc);
    common::detail::json::read(obj, "totalLockedInUSDT", out.total_locked_in_usdt);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SimpleAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAmountInBTC", v.total_amount_in_btc);
    common::detail::json::write(obj, "totalAmountInUSDT", v.total_amount_in_usdt);
    common::detail::json::write(obj, "totalFlexibleAmountInBTC", v.total_flexible_amount_in_btc);
    common::detail::json::write(obj, "totalFlexibleAmountInUSDT", v.total_flexible_amount_in_usdt);
    common::detail::json::write(obj, "totalLockedInBTC", v.total_locked_in_btc);
    common::detail::json::write(obj, "totalLockedInUSDT", v.total_locked_in_usdt);
}

} // namespace binance::simple_earn::rest_api
