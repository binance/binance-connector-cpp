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

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct CorporateActionRecordsResponseItemsInner {
    /// Unique record ID.
    std::optional<std::int64_t> id;
    /// User ID.
    std::optional<std::int64_t> user_id;
    /// Asset code, the unique identifier of the stock in the system, for example `EQ_AAPL`.
    /// Currently all asset codes carry the `EQ_` prefix.
    std::optional<std::string> asset_code;
    /// Corporate action event type. Values include `CASH_DIVIDEND`, `STOCK_DIVIDEND`,
    /// `FORWARD_SPLIT`, `REVERSE_SPLIT`, `SPIN_OFF`, `CASH_MERGER`, `STOCK_MERGER`,
    /// `STOCK_AND_CASH_MERGER`, `WORTHLESS_REMOVAL`, `NAME_CHANGE` and `RIGHTS_DISTRIBUTION`.
    std::optional<std::string> event_type;
    /// Signed change of the asset quantity, including free and frozen balances.
    std::optional<std::string> amount;
    /// Last modification time (ms epoch).
    std::optional<std::int64_t> db_modify_time;

    bool operator==(const CorporateActionRecordsResponseItemsInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT CorporateActionRecordsResponseItemsInner
tag_invoke(boost::json::value_to_tag<CorporateActionRecordsResponseItemsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const CorporateActionRecordsResponseItemsInner& v);

} // namespace binance::stocks::rest_api
