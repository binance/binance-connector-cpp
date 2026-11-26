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

struct GetAllMarginAssetsResponseInner {
    /// asset Full Name.
    std::optional<std::string> asset_full_name;
    /// asset Name.
    std::optional<std::string> asset_name;
    /// is Borrowable.
    std::optional<bool> is_borrowable;
    /// is Mortgageable.
    std::optional<bool> is_mortgageable;
    /// user Min Borrow.
    std::optional<std::string> user_min_borrow;
    /// user Min Repay.
    std::optional<std::string> user_min_repay;
    /// delist Time.
    std::optional<std::int64_t> delist_time;

    bool operator==(const GetAllMarginAssetsResponseInner& /*other*/) const = default;
};

BINANCE_MARGIN_TRADING_EXPORT GetAllMarginAssetsResponseInner
tag_invoke(boost::json::value_to_tag<GetAllMarginAssetsResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetAllMarginAssetsResponseInner& v);

} // namespace binance::margin_trading::rest_api
