//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/index_price_and_mark_price_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

IndexPriceAndMarkPriceResponseInner
tag_invoke(boost::json::value_to_tag<IndexPriceAndMarkPriceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "IndexPriceAndMarkPriceResponseInner");
    IndexPriceAndMarkPriceResponseInner out;
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "pair", out.pair);
    common::detail::json::read(obj, "markPrice", out.mark_price);
    common::detail::json::read(obj, "indexPrice", out.index_price);
    common::detail::json::read(obj, "estimatedSettlePrice", out.estimated_settle_price);
    common::detail::json::read(obj, "lastFundingRate", out.last_funding_rate);
    common::detail::json::read(obj, "interestRate", out.interest_rate);
    common::detail::json::read(obj, "nextFundingTime", out.next_funding_time);
    common::detail::json::read(obj, "time", out.time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const IndexPriceAndMarkPriceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "pair", v.pair);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "indexPrice", v.index_price);
    common::detail::json::write(obj, "estimatedSettlePrice", v.estimated_settle_price);
    common::detail::json::write(obj, "lastFundingRate", v.last_funding_rate);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "nextFundingTime", v.next_funding_time);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
