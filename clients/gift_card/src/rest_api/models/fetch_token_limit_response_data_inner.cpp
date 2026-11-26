//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/gift_card/rest_api/models/fetch_token_limit_response_data_inner.hpp>

namespace binance::gift_card::rest_api {

FetchTokenLimitResponseDataInner
tag_invoke(boost::json::value_to_tag<FetchTokenLimitResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "FetchTokenLimitResponseDataInner");
    FetchTokenLimitResponseDataInner out;
    common::detail::json::read(obj, "coin", out.coin);
    common::detail::json::read(obj, "fromMin", out.from_min);
    common::detail::json::read(obj, "fromMax", out.from_max);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const FetchTokenLimitResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "coin", v.coin);
    common::detail::json::write(obj, "fromMin", v.from_min);
    common::detail::json::write(obj, "fromMax", v.from_max);
}

} // namespace binance::gift_card::rest_api
