//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_streams/models/contract_info_stream_response_bks_inner.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_streams {

ContractInfoStreamResponseBksInner
tag_invoke(boost::json::value_to_tag<ContractInfoStreamResponseBksInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ContractInfoStreamResponseBksInner");
    ContractInfoStreamResponseBksInner out;
    common::detail::json::read(obj, "bs", out.bs);
    common::detail::json::read(obj, "bnf", out.bnf);
    common::detail::json::read(obj, "bnc", out.bnc);
    common::detail::json::read(obj, "mmr", out.mmr);
    common::detail::json::read(obj, "cf", out.cf);
    common::detail::json::read(obj, "mi", out.mi);
    common::detail::json::read(obj, "ma", out.ma);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ContractInfoStreamResponseBksInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "bs", v.bs);
    common::detail::json::write(obj, "bnf", v.bnf);
    common::detail::json::write(obj, "bnc", v.bnc);
    common::detail::json::write(obj, "mmr", v.mmr);
    common::detail::json::write(obj, "cf", v.cf);
    common::detail::json::write(obj, "mi", v.mi);
    common::detail::json::write(obj, "ma", v.ma);
}

} // namespace binance::derivatives_trading_coin_futures::websocket_streams
