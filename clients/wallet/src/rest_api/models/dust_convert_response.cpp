//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/dust_convert_response.hpp>

namespace binance::wallet::rest_api {

DustConvertResponse tag_invoke(boost::json::value_to_tag<DustConvertResponse> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "DustConvertResponse");
    DustConvertResponse out;
    common::detail::json::read(obj, "totalTransfered", out.total_transfered);
    common::detail::json::read(obj, "totalServiceCharge", out.total_service_charge);
    common::detail::json::read(obj, "transferResult", out.transfer_result);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const DustConvertResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "totalTransfered", v.total_transfered);
    common::detail::json::write(obj, "totalServiceCharge", v.total_service_charge);
    common::detail::json::write(obj, "transferResult", v.transfer_result);
}

} // namespace binance::wallet::rest_api
