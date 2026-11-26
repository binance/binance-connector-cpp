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

struct WithdrawTravelRuleResponse {
    /// The travel rule record Id
    std::optional<std::int64_t> tr_id;
    /// Whether the withdraw request is accepted
    std::optional<bool> accepted;
    /// The detailed infomation of the withdrawal result.
    std::optional<std::string> info;

    bool operator==(const WithdrawTravelRuleResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT WithdrawTravelRuleResponse tag_invoke(
    boost::json::value_to_tag<WithdrawTravelRuleResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const WithdrawTravelRuleResponse& v);

} // namespace binance::wallet::rest_api
