//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/query_max_transfer_out_amount_response.hpp>

namespace binance::margin_trading::rest_api {

QueryMaxTransferOutAmountResponse
tag_invoke(boost::json::value_to_tag<QueryMaxTransferOutAmountResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "QueryMaxTransferOutAmountResponse");
    QueryMaxTransferOutAmountResponse out;
    common::detail::json::read(obj, "amount", out.amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const QueryMaxTransferOutAmountResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "amount", v.amount);
}

} // namespace binance::margin_trading::rest_api
