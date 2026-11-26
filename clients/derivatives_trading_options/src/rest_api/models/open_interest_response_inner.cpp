//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/models/open_interest_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

OpenInterestResponseInner tag_invoke(boost::json::value_to_tag<OpenInterestResponseInner> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenInterestResponseInner");
    OpenInterestResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "sumOpenInterest", out.sum_open_interest);
    common::detail::json::read(obj, "sumOpenInterestUsd", out.sum_open_interest_usd);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenInterestResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "sumOpenInterest", v.sum_open_interest);
    common::detail::json::write(obj, "sumOpenInterestUsd", v.sum_open_interest_usd);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_options::rest_api
