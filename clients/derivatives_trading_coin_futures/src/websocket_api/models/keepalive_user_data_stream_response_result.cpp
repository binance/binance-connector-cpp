//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/keepalive_user_data_stream_response_result.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

KeepaliveUserDataStreamResponseResult
tag_invoke(boost::json::value_to_tag<KeepaliveUserDataStreamResponseResult> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "KeepaliveUserDataStreamResponseResult");
    KeepaliveUserDataStreamResponseResult out;
    common::detail::json::read(obj, "listenKey", out.listen_key);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const KeepaliveUserDataStreamResponseResult& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "listenKey", v.listen_key);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_api
