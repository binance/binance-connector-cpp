//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct GetCountryListResponseCountriesInner {
    /// ISO 2-digit country code, lowercase.
    std::optional<std::string> country_code;
    /// Country display name.
    std::optional<std::string> country_name;
    /// `supported`, `limited`, or `blocked`.
    std::optional<std::string> block_type;
    /// Whether deposit is allowed for this country.
    std::optional<bool> deposit_allowed;
    /// Whether withdrawal is allowed for this country.
    std::optional<bool> withdrawal_allowed;
    /// Whether this country has region-level restrictions. Always `false` for the BR entity, which
    /// does not collect region/city.
    std::optional<bool> has_region_restrictions;

    bool operator==(const GetCountryListResponseCountriesInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetCountryListResponseCountriesInner
tag_invoke(boost::json::value_to_tag<GetCountryListResponseCountriesInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetCountryListResponseCountriesInner& v);

} // namespace binance::wallet::rest_api
