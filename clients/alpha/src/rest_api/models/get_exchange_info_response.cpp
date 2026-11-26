//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/get_exchange_info_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

GetExchangeInfoResponse tag_invoke(boost::json::value_to_tag<GetExchangeInfoResponse> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetExchangeInfoResponse");
    GetExchangeInfoResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "messageDetail", out.message_detail);
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "data", out.data);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetExchangeInfoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "messageDetail", v.message_detail);
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "data", v.data);
}

} // namespace binance::alpha::rest_api
