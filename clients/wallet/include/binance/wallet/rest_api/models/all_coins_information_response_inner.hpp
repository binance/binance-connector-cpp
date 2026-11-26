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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner_network_list_inner.hpp>

namespace binance::wallet::rest_api {

struct AllCoinsInformationResponseInner {
    std::optional<std::string> coin;
    std::optional<bool> deposit_all_enable;
    std::optional<bool> withdraw_all_enable;
    std::optional<std::string> name;
    std::optional<std::string> free;
    std::optional<std::string> locked;
    std::optional<std::string> freeze;
    std::optional<std::string> withdrawing;
    std::optional<std::string> ipoing;
    std::optional<std::string> ipoable;
    std::optional<std::string> storage;
    std::optional<bool> is_legal_money;
    std::optional<bool> trading;
    std::optional<std::vector<AllCoinsInformationResponseInnerNetworkListInner>> network_list;

    bool operator==(const AllCoinsInformationResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AllCoinsInformationResponseInner
tag_invoke(boost::json::value_to_tag<AllCoinsInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AllCoinsInformationResponseInner& v);

} // namespace binance::wallet::rest_api
