//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/create_outbound_transfer_response.hpp>

namespace binance::w3w_prediction::rest_api {

CreateOutboundTransferResponse
tag_invoke(boost::json::value_to_tag<CreateOutboundTransferResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateOutboundTransferResponse");
    CreateOutboundTransferResponse out;
    common::detail::json::read(obj, "transferId", out.transfer_id);
    common::detail::json::read(obj, "status", out.status);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateOutboundTransferResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "transferId", v.transfer_id);
    common::detail::json::write(obj, "status", v.status);
}

} // namespace binance::w3w_prediction::rest_api
