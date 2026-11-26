//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/start_user_data_stream_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

StartUserDataStreamResponse
tag_invoke(boost::json::value_to_tag<StartUserDataStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StartUserDataStreamResponse");
    StartUserDataStreamResponse out;
    common::detail::json::read(obj, "listenKey", out.listen_key);
    common::detail::json::read(obj, "expiration", out.expiration);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StartUserDataStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "listenKey", v.listen_key);
    common::detail::json::write(obj, "expiration", v.expiration);
}

} // namespace binance::derivatives_trading_options::rest_api
