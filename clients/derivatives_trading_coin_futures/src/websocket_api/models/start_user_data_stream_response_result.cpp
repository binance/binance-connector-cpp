//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/start_user_data_stream_response_result.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

StartUserDataStreamResponseResult
tag_invoke(boost::json::value_to_tag<StartUserDataStreamResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "StartUserDataStreamResponseResult");
    StartUserDataStreamResponseResult out;
    common::detail::json::read(obj, "listenKey", out.listen_key);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const StartUserDataStreamResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "listenKey", v.listen_key);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_api
