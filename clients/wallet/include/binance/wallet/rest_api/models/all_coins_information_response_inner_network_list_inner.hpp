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

struct AllCoinsInformationResponseInnerNetworkListInner {
    std::optional<std::string> network;
    std::optional<std::string> coin;
    std::optional<std::string> withdraw_integer_multiple;
    std::optional<bool> is_default;
    std::optional<bool> deposit_enable;
    std::optional<bool> withdraw_enable;
    /// shown only when "depositEnable" is false.
    std::optional<std::string> deposit_desc;
    /// shown only when "withdrawEnable" is false.
    std::optional<std::string> withdraw_desc;
    std::optional<std::string> special_tips;
    std::optional<std::string> special_withdraw_tips;
    std::optional<std::string> name;
    std::optional<bool> reset_address_status;
    std::optional<std::string> address_regex;
    std::optional<std::string> memo_regex;
    std::optional<std::string> withdraw_fee;
    std::optional<std::string> withdraw_min;
    std::optional<std::string> withdraw_max;
    /// Minimum internal transfer amount
    std::optional<std::string> withdraw_internal_min;
    std::optional<std::string> deposit_dust;
    /// min number for balance confirmation
    std::optional<std::int64_t> min_confirm;
    /// confirmation number for balance unlock
    std::optional<std::int64_t> un_lock_confirm;
    /// Obsoleted, recomment to use withdrawTag
    std::optional<bool> same_address;
    /// If the coin needs to provide memo to withdraw
    std::optional<bool> withdraw_tag;
    std::optional<std::int64_t> estimated_arrival_time;
    std::optional<bool> busy;
    std::optional<std::string> contract_address_url;
    std::optional<std::string> contract_address;
    /// 1 1MBABYDOGE = 1000000 BABYDOGE
    std::optional<std::int64_t> denomination;

    bool
    operator==(const AllCoinsInformationResponseInnerNetworkListInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AllCoinsInformationResponseInnerNetworkListInner
tag_invoke(boost::json::value_to_tag<AllCoinsInformationResponseInnerNetworkListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AllCoinsInformationResponseInnerNetworkListInner& v);

} // namespace binance::wallet::rest_api
