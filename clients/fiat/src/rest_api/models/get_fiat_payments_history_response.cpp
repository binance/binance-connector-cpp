//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/fiat/rest_api/models/get_fiat_payments_history_response.hpp>

namespace binance::fiat::rest_api {

GetFiatPaymentsHistoryResponse
tag_invoke(boost::json::value_to_tag<GetFiatPaymentsHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetFiatPaymentsHistoryResponse");
    GetFiatPaymentsHistoryResponse out;
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "message", out.message);
    common::detail::json::read(obj, "data", out.data);
    common::detail::json::read(obj, "total", out.total);
    common::detail::json::read(obj, "success", out.success);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetFiatPaymentsHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "message", v.message);
    common::detail::json::write(obj, "data", v.data);
    common::detail::json::write(obj, "total", v.total);
    common::detail::json::write(obj, "success", v.success);
}

} // namespace binance::fiat::rest_api
