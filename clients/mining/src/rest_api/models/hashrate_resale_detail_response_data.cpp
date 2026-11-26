//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/hashrate_resale_detail_response_data.hpp>

namespace binance::mining::rest_api {

HashrateResaleDetailResponseData
tag_invoke(boost::json::value_to_tag<HashrateResaleDetailResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "HashrateResaleDetailResponseData");
    HashrateResaleDetailResponseData out;
    common::detail::json::read(obj, "profitTransferDetails", out.profit_transfer_details);
    common::detail::json::read(obj, "totalNum", out.total_num);
    common::detail::json::read(obj, "pageSize", out.page_size);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const HashrateResaleDetailResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "profitTransferDetails", v.profit_transfer_details);
    common::detail::json::write(obj, "totalNum", v.total_num);
    common::detail::json::write(obj, "pageSize", v.page_size);
}

} // namespace binance::mining::rest_api
