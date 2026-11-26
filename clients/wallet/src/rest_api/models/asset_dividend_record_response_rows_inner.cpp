//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/asset_dividend_record_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

AssetDividendRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<AssetDividendRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AssetDividendRecordResponseRowsInner");
    AssetDividendRecordResponseRowsInner out;
    common::detail::json::read(obj, "id", out.id);
    common::detail::json::read(obj, "amount", out.amount);
    common::detail::json::read(obj, "asset", out.asset);
    common::detail::json::read(obj, "divTime", out.div_time);
    common::detail::json::read(obj, "enInfo", out.en_info);
    common::detail::json::read(obj, "tranId", out.tran_id);
    common::detail::json::read(obj, "direction", out.direction);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AssetDividendRecordResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "id", v.id);
    common::detail::json::write(obj, "amount", v.amount);
    common::detail::json::write(obj, "asset", v.asset);
    common::detail::json::write(obj, "divTime", v.div_time);
    common::detail::json::write(obj, "enInfo", v.en_info);
    common::detail::json::write(obj, "tranId", v.tran_id);
    common::detail::json::write(obj, "direction", v.direction);
}

} // namespace binance::wallet::rest_api
