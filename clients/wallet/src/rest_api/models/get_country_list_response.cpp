//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response.hpp>

namespace binance::wallet::rest_api {

GetCountryListResponse tag_invoke(boost::json::value_to_tag<GetCountryListResponse> /*tag*/,
                                  const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCountryListResponse");
    GetCountryListResponse out;
    common::detail::json::read(obj, "countries", out.countries);
    common::detail::json::read(obj, "lastUpdated", out.last_updated);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCountryListResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "countries", v.countries);
    common::detail::json::write(obj, "lastUpdated", v.last_updated);
}

} // namespace binance::wallet::rest_api
