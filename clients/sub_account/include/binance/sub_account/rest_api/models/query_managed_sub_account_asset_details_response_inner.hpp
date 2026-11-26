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

struct QueryManagedSubAccountAssetDetailsResponseInner {
    std::optional<std::string> coin;
    std::optional<std::string> name;
    std::optional<std::string> total_balance;
    std::optional<std::string> available_balance;
    std::optional<std::string> in_order;
    std::optional<std::string> btc_value;

    bool
    operator==(const QueryManagedSubAccountAssetDetailsResponseInner& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT QueryManagedSubAccountAssetDetailsResponseInner
tag_invoke(boost::json::value_to_tag<QueryManagedSubAccountAssetDetailsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const QueryManagedSubAccountAssetDetailsResponseInner& v);

} // namespace binance::sub_account::rest_api
