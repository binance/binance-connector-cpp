//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/mark_price_response2_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

MarkPriceResponse2Inner tag_invoke(boost::json::value_to_tag<MarkPriceResponse2Inner> /*tag*/,
                                   const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "MarkPriceResponse2Inner");
    MarkPriceResponse2Inner out;
    common::detail::json::read(obj, "symbol", out.symbol);
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
                const MarkPriceResponse2Inner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "markPrice", v.mark_price);
    common::detail::json::write(obj, "indexPrice", v.index_price);
    common::detail::json::write(obj, "estimatedSettlePrice", v.estimated_settle_price);
    common::detail::json::write(obj, "lastFundingRate", v.last_funding_rate);
    common::detail::json::write(obj, "interestRate", v.interest_rate);
    common::detail::json::write(obj, "nextFundingTime", v.next_funding_time);
    common::detail::json::write(obj, "time", v.time);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
