//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/bstocks_corporate_action_records_response.hpp>

namespace binance::stocks::rest_api {

BstocksCorporateActionRecordsResponse
tag_invoke(boost::json::value_to_tag<BstocksCorporateActionRecordsResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "BstocksCorporateActionRecordsResponse");
    BstocksCorporateActionRecordsResponse out;
    common::detail::json::read(obj, "items", out.items);
    common::detail::json::read(obj, "nextTime", out.next_time);
    common::detail::json::read(obj, "nextId", out.next_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const BstocksCorporateActionRecordsResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "items", v.items);
    common::detail::json::write(obj, "nextTime", v.next_time);
    common::detail::json::write(obj, "nextId", v.next_id);
}

} // namespace binance::stocks::rest_api
