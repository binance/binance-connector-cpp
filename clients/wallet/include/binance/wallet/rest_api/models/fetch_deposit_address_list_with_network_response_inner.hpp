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
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct FetchDepositAddressListWithNetworkResponseInner {
    /// coin here means network address space, ETH for all EVM-like network
    std::optional<std::string> coin;
    std::optional<std::string> address;
    std::optional<std::string> tag;
    /// 'isDefault' is 1 means the address is default, same as shown in the app.
    std::optional<std::int64_t> is_default;

    bool
    operator==(const FetchDepositAddressListWithNetworkResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT FetchDepositAddressListWithNetworkResponseInner
tag_invoke(boost::json::value_to_tag<FetchDepositAddressListWithNetworkResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const FetchDepositAddressListWithNetworkResponseInner& v);

} // namespace binance::wallet::rest_api
