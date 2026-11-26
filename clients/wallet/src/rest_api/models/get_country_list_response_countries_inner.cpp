//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response_countries_inner.hpp>

namespace binance::wallet::rest_api {

GetCountryListResponseCountriesInner
tag_invoke(boost::json::value_to_tag<GetCountryListResponseCountriesInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetCountryListResponseCountriesInner");
    GetCountryListResponseCountriesInner out;
    common::detail::json::read(obj, "countryCode", out.country_code);
    common::detail::json::read(obj, "countryName", out.country_name);
    common::detail::json::read(obj, "blockType", out.block_type);
    common::detail::json::read(obj, "depositAllowed", out.deposit_allowed);
    common::detail::json::read(obj, "withdrawalAllowed", out.withdrawal_allowed);
    common::detail::json::read(obj, "hasRegionRestrictions", out.has_region_restrictions);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCountryListResponseCountriesInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "countryCode", v.country_code);
    common::detail::json::write(obj, "countryName", v.country_name);
    common::detail::json::write(obj, "blockType", v.block_type);
    common::detail::json::write(obj, "depositAllowed", v.deposit_allowed);
    common::detail::json::write(obj, "withdrawalAllowed", v.withdrawal_allowed);
    common::detail::json::write(obj, "hasRegionRestrictions", v.has_region_restrictions);
}

} // namespace binance::wallet::rest_api
