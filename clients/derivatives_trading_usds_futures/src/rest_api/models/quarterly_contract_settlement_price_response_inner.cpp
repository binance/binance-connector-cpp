//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/quarterly_contract_settlement_price_response_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

QuarterlyContractSettlementPriceResponseInner
tag_invoke(boost::json::value_to_tag<QuarterlyContractSettlementPriceResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "QuarterlyContractSettlementPriceResponseInner");
    QuarterlyContractSettlementPriceResponseInner out;
    common::detail::json::read(obj, "deliveryTime", out.delivery_time);
    common::detail::json::read(obj, "deliveryPrice", out.delivery_price);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuarterlyContractSettlementPriceResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "deliveryTime", v.delivery_time);
    common::detail::json::write(obj, "deliveryPrice", v.delivery_price);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
