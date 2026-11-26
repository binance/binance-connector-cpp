//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_funds_detail_inner.hpp>

namespace binance::pay::rest_api {

GetPayTradeHistoryResponseDataInnerFundsDetailInner
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInnerFundsDetailInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetPayTradeHistoryResponseDataInnerFundsDetailInner");
    GetPayTradeHistoryResponseDataInnerFundsDetailInner out;
    common::detail::json::read(obj, "currency", out.currency);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "walletAssetCost", out.wallet_asset_cost);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetPayTradeHistoryResponseDataInnerFundsDetailInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "currency", v.currency);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "walletAssetCost", v.wallet_asset_cost);
}

} // namespace binance::pay::rest_api
