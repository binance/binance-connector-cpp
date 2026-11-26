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

struct BrokerWithdrawResponse {
    /// The travel rule record Id
    std::optional<std::int64_t> tr_id;
    /// Whether the withdraw request is accepted
    std::optional<bool> accepted;
    /// The detailed infomation of the withdrawal result.
    std::optional<std::string> info;

    bool operator==(const BrokerWithdrawResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT BrokerWithdrawResponse
tag_invoke(boost::json::value_to_tag<BrokerWithdrawResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const BrokerWithdrawResponse& v);

} // namespace binance::wallet::rest_api
