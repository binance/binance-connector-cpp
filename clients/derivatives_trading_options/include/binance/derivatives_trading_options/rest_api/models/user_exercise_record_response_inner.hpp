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

#include <binance/derivatives_trading_options/export.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct UserExerciseRecordResponseInner {
    /// id
    std::optional<std::string> id;
    /// currency
    std::optional<std::string> currency;
    /// symbol
    std::optional<std::string> symbol;
    /// exercise Price
    std::optional<std::string> exercise_price;
    /// quantity
    std::optional<std::string> quantity;
    /// amount
    std::optional<std::string> amount;
    /// fee
    std::optional<std::string> fee;
    /// create Date
    std::optional<std::int64_t> create_date;
    /// price Scale
    std::optional<std::int64_t> price_scale;
    /// quantity Scale
    std::optional<std::int64_t> quantity_scale;
    /// option Side
    std::optional<std::string> option_side;
    /// position Side
    std::optional<std::string> position_side;
    /// quote Asset
    std::optional<std::string> quote_asset;

    bool operator==(const UserExerciseRecordResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT UserExerciseRecordResponseInner
tag_invoke(boost::json::value_to_tag<UserExerciseRecordResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const UserExerciseRecordResponseInner& v);

} // namespace binance::derivatives_trading_options::rest_api
