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

#include <binance/margin_trading/export.hpp>

namespace binance::margin_trading::rest_api {

struct QueryMarginAccountsTradeListResponseInner {
    /// commission.
    std::optional<std::string> commission;
    /// commission Asset.
    std::optional<std::string> commission_asset;
    /// id.
    std::optional<std::int64_t> id;
    /// is Best Match.
    std::optional<bool> is_best_match;
    /// is Buyer.
    std::optional<bool> is_buyer;
    /// is Maker.
    std::optional<bool> is_maker;
    /// order Id.
    std::optional<std::int64_t> order_id;
    /// price.
    std::optional<std::string> price;
    /// qty.
    std::optional<std::string> qty;
    /// symbol.
    std::optional<std::string> symbol;
    /// is Isolated.
    std::optional<bool> is_isolated;
    /// time.
    std::optional<std::int64_t> time;

    bool operator==(const QueryMarginAccountsTradeListResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT QueryMarginAccountsTradeListResponseInner
tag_invoke(boost::json::value_to_tag<QueryMarginAccountsTradeListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryMarginAccountsTradeListResponseInner& v);

} // namespace binance::margin_trading::rest_api
