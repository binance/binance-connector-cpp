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

#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner_legs_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct AccountBlockTradeListResponseInner {
    /// parent Order Id
    std::optional<std::string> parent_order_id;
    /// cross Type
    std::optional<std::string> cross_type;
    /// legs
    std::optional<std::vector<AccountBlockTradeListResponseInnerLegsInner>> legs;
    /// block Trade Settlement Key
    std::optional<std::string> block_trade_settlement_key;

    bool operator==(const AccountBlockTradeListResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT AccountBlockTradeListResponseInner
tag_invoke(boost::json::value_to_tag<AccountBlockTradeListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const AccountBlockTradeListResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
