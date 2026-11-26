//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/universal_transfer_response.hpp>

namespace binance::sub_account::rest_api {

UniversalTransferResponse tag_invoke(boost::json::value_to_tag<UniversalTransferResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UniversalTransferResponse");
    UniversalTransferResponse out;
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "clientTranId", out.client_tran_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UniversalTransferResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "clientTranId", v.client_tran_id);
}

} // namespace binance::sub_account::rest_api
