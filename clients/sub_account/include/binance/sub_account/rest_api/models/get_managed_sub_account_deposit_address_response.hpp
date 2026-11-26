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

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct GetManagedSubAccountDepositAddressResponse {
    std::optional<std::string> coin;
    std::optional<std::string> address;
    std::optional<std::string> tag;
    std::optional<std::string> url;

    bool operator==(const GetManagedSubAccountDepositAddressResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetManagedSubAccountDepositAddressResponse
tag_invoke(boost::json::value_to_tag<GetManagedSubAccountDepositAddressResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetManagedSubAccountDepositAddressResponse& v);

} // namespace binance::sub_account::rest_api
