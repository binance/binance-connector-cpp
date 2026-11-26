//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/algo/rest_api/models/volume_participation_future_algo_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

VolumeParticipationFutureAlgoResponse
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "VolumeParticipationFutureAlgoResponse");
    VolumeParticipationFutureAlgoResponse out;
    common::detail::json::read(obj, "clientAlgoId", out.client_algo_id);
    common::detail::json::read(obj, "success", out.success);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "msg", out.msg);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VolumeParticipationFutureAlgoResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "clientAlgoId", v.client_algo_id);
    common::detail::json::write(obj, "success", v.success);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "msg", v.msg);
}

} // namespace binance::algo::rest_api
