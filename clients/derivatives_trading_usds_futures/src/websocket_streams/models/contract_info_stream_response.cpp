//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/websocket_streams/models/contract_info_stream_response.hpp>

namespace binance::derivatives_trading_usds_futures::websocket_streams {

ContractInfoStreamResponse tag_invoke(boost::json::value_to_tag<ContractInfoStreamResponse> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ContractInfoStreamResponse");
    ContractInfoStreamResponse out;
    common::detail::json::read(obj, "e", out.e);
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "s", out.s);
    common::detail::json::read(obj, "ct", out.ct);
    common::detail::json::read(obj, "dt", out.dt);
    common::detail::json::read(obj, "ot", out.ot);
    common::detail::json::read(obj, "cs", out.cs);
    common::detail::json::read(obj, "bks", out.bks);
    common::detail::json::read(obj, "st", out.st);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ContractInfoStreamResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "e", v.e);
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "s", v.s);
    common::detail::json::write(obj, "ct", v.ct);
    common::detail::json::write(obj, "dt", v.dt);
    common::detail::json::write(obj, "ot", v.ot);
    common::detail::json::write(obj, "cs", v.cs);
    common::detail::json::write(obj, "bks", v.bks);
    common::detail::json::write(obj, "st", v.st);
}

} // namespace binance::derivatives_trading_usds_futures::websocket_streams
