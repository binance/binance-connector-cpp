//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response_countries_inner.hpp>

namespace binance::wallet::rest_api {

struct GetCountryListResponse {
    std::optional<std::vector<GetCountryListResponseCountriesInner>> countries;
    /// Last data update timestamp (epoch milliseconds); 0 if empty.
    std::optional<std::int64_t> last_updated;

    bool operator==(const GetCountryListResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetCountryListResponse
tag_invoke(boost::json::value_to_tag<GetCountryListResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetCountryListResponse& v);

} // namespace binance::wallet::rest_api
