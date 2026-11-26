//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/staking/rest_api/models/on_chain_yields_account_response.hpp>

namespace binance::staking::rest_api {

OnChainYieldsAccountResponse
tag_invoke(boost::json::value_to_tag<OnChainYieldsAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OnChainYieldsAccountResponse");
    OnChainYieldsAccountResponse out;
    common::detail::json::read(obj, "totalAmountInBTC", out.total_amount_in_btc);
    common::detail::json::read(obj, "totalAmountInUSDT", out.total_amount_in_usdt);
    common::detail::json::read(obj, "totalFlexibleAmountInBTC", out.total_flexible_amount_in_btc);
    common::detail::json::read(obj, "totalFlexibleAmountInUSDT", out.total_flexible_amount_in_usdt);
    common::detail::json::read(obj, "totalLockedInBTC", out.total_locked_in_btc);
    common::detail::json::read(obj, "totalLockedInUSDT", out.total_locked_in_usdt);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OnChainYieldsAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalAmountInBTC", v.total_amount_in_btc);
    common::detail::json::write(obj, "totalAmountInUSDT", v.total_amount_in_usdt);
    common::detail::json::write(obj, "totalFlexibleAmountInBTC", v.total_flexible_amount_in_btc);
    common::detail::json::write(obj, "totalFlexibleAmountInUSDT", v.total_flexible_amount_in_usdt);
    common::detail::json::write(obj, "totalLockedInBTC", v.total_locked_in_btc);
    common::detail::json::write(obj, "totalLockedInUSDT", v.total_locked_in_usdt);
}

} // namespace binance::staking::rest_api
