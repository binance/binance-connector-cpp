//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/websocket_streams/models/contract_kline_stream_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::websocket_streams {

ContractKlineStreamResponse
tag_invoke(boost::json::value_to_tag<ContractKlineStreamResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ContractKlineStreamResponse");
    ContractKlineStreamResponse out;
    common::detail::json::read(obj, "ca", out.ca);
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "k", out.k);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ContractKlineStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "ca", v.ca);
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "k", v.k);
}

} // namespace binance::alpha::websocket_streams
