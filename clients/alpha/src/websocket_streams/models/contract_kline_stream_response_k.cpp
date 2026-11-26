//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/websocket_streams/models/contract_kline_stream_response_k.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::websocket_streams {

ContractKlineStreamResponseK
tag_invoke(boost::json::value_to_tag<ContractKlineStreamResponseK> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ContractKlineStreamResponseK");
    ContractKlineStreamResponseK out;
    common::detail::json::read(obj, "o", out.o);
    common::detail::json::read(obj, "c", out.c);
    common::detail::json::read(obj, "h", out.h);
    common::detail::json::read(obj, "l", out.l);
    common::detail::json::read(obj, "v", out.v);
    common::detail::json::read(obj, "ot", out.ot);
    common::detail::json::read(obj, "ct", out.ct);
    common::detail::json::read(obj, "i", out.i);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ContractKlineStreamResponseK& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "o", v.o);
    common::detail::json::write(obj, "c", v.c);
    common::detail::json::write(obj, "h", v.h);
    common::detail::json::write(obj, "l", v.l);
    common::detail::json::write(obj, "v", v.v);
    common::detail::json::write(obj, "ot", v.ot);
    common::detail::json::write(obj, "ct", v.ct);
    common::detail::json::write(obj, "i", v.i);
}

} // namespace binance::alpha::websocket_streams
