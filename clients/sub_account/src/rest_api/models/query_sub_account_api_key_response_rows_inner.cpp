//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/sub_account/rest_api/models/query_sub_account_api_key_response_rows_inner.hpp>

namespace binance::sub_account::rest_api {

QuerySubAccountApiKeyResponseRowsInner
tag_invoke(boost::json::value_to_tag<QuerySubAccountApiKeyResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QuerySubAccountApiKeyResponseRowsInner");
    QuerySubAccountApiKeyResponseRowsInner out;
    common::detail::json::read(obj, "email", out.email);
    common::detail::json::read(obj, "apiName", out.api_name);
    common::detail::json::read(obj, "apikey", out.apikey);
    common::detail::json::read(obj, "canTrade", out.can_trade);
    common::detail::json::read(obj, "canMarginLoanRepay", out.can_margin_loan_repay);
    common::detail::json::read(obj, "canFuturesTrade", out.can_futures_trade);
    common::detail::json::read(obj, "canUniversalTransfer", out.can_universal_transfer);
    common::detail::json::read(obj, "canVanillaOptions", out.can_vanilla_options);
    common::detail::json::read(obj, "canFixApiTrading", out.can_fix_api_trading);
    common::detail::json::read(obj, "canFixApiReading", out.can_fix_api_reading);
    common::detail::json::read(obj, "timestamp", out.timestamp);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QuerySubAccountApiKeyResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "email", v.email);
    common::detail::json::write(obj, "apiName", v.api_name);
    common::detail::json::write(obj, "apikey", v.apikey);
    common::detail::json::write(obj, "canTrade", v.can_trade);
    common::detail::json::write(obj, "canMarginLoanRepay", v.can_margin_loan_repay);
    common::detail::json::write(obj, "canFuturesTrade", v.can_futures_trade);
    common::detail::json::write(obj, "canUniversalTransfer", v.can_universal_transfer);
    common::detail::json::write(obj, "canVanillaOptions", v.can_vanilla_options);
    common::detail::json::write(obj, "canFixApiTrading", v.can_fix_api_trading);
    common::detail::json::write(obj, "canFixApiReading", v.can_fix_api_reading);
    common::detail::json::write(obj, "timestamp", v.timestamp);
}

} // namespace binance::sub_account::rest_api
