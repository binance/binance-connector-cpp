//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/deposit_assets_into_the_managed_sub_account_response.hpp>

namespace binance::sub_account::rest_api {

DepositAssetsIntoTheManagedSubAccountResponse
tag_invoke(boost::json::value_to_tag<DepositAssetsIntoTheManagedSubAccountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "DepositAssetsIntoTheManagedSubAccountResponse");
    DepositAssetsIntoTheManagedSubAccountResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DepositAssetsIntoTheManagedSubAccountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
}

} // namespace binance::sub_account::rest_api
