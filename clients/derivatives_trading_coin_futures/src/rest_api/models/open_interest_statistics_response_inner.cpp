//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/open_interest_statistics_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

OpenInterestStatisticsResponseInner
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OpenInterestStatisticsResponseInner");
    OpenInterestStatisticsResponseInner out;
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "contractType", out.contract_type);
    common::detail::json::read(obj, "sumOpenInterest", out.sum_open_interest);
    common::detail::json::read(obj, "sumOpenInterestValue", out.sum_open_interest_value);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OpenInterestStatisticsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "contractType", v.contract_type);
    common::detail::json::write(obj, "sumOpenInterest", v.sum_open_interest);
    common::detail::json::write(obj, "sumOpenInterestValue", v.sum_open_interest_value);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
