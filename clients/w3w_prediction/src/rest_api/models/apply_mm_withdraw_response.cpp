//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/apply_mm_withdraw_response.hpp>

namespace binance::w3w_prediction::rest_api {

ApplyMmWithdrawResponse tag_invoke(boost::json::value_to_tag<ApplyMmWithdrawResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ApplyMmWithdrawResponse");
    ApplyMmWithdrawResponse out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "walletId", out.wallet_id);
    common::detail::json::read(obj, "walletAddress", out.wallet_address);
    common::detail::json::read(obj, "transferId", out.transfer_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ApplyMmWithdrawResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "walletId", v.wallet_id);
    common::detail::json::write(obj, "walletAddress", v.wallet_address);
    common::detail::json::write(obj, "transferId", v.transfer_id);
}

} // namespace binance::w3w_prediction::rest_api
