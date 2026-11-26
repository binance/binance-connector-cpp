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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_detail_response_collateral_release_inner.hpp>
#include <binance/stock_options/rest_api/models/option_settlement_event_history_response_rows_inner_deliverables_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionSettlementEventDetailResponse {
    /// Event ID; use it with Option Settlement Event Detail.
    std::optional<std::string> event_id;
    /// `EXERCISE` / `ASSIGNMENT` / `EXPIRY`.
    std::optional<std::string> event_type;
    /// Event status. Only settled events are returned, so the value is always `Completed`.
    std::optional<std::string> status;
    /// OCC option contract symbol.
    std::optional<std::string> symbol;
    /// Underlying US-equity ticker.
    std::optional<std::string> underlying_symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Number of contracts, **absolute value** (unsigned), unlike the history endpoint.
    std::optional<std::string> contracts;
    /// Expiration date as the millisecond timestamp of 12:00 ET on the expiration day. Convert in
    /// `America/New_York` and take the date part (see General Info).
    std::optional<std::int64_t> expiration_date;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Net change in underlying shares (signed). Not returned for `EXPIRY` events, or for events on
    /// adjusted contracts that deliver more than one stock (see `deliverables`).
    std::optional<std::string> share_delta;
    /// Assets actually delivered. Empty array when nothing is delivered.
    std::optional<std::vector<OptionSettlementEventHistoryResponseRowsInnerDeliverablesInner>>
        deliverables;
    /// Time the settlement record was created (ms).
    std::optional<std::int64_t> event_time;
    /// Settlement method: `PHYSICAL` (physical delivery) / `CASH` (cash settlement) / `MIXED`
    /// (both). Not returned for `EXPIRY` events.
    std::optional<std::string> settlement_kind;
    /// Reference price of the underlying when the event was generated, for display only; it is not
    /// used in the settlement calculation. Not returned if unavailable.
    std::optional<std::string> underlying_price;
    /// Cash direction: `DEBIT` / `CREDIT`. Not returned for `EXPIRY` events.
    std::optional<std::string> cash_direction;
    /// Net cash amount (absolute value); see `cashDirection` for the direction. Not returned for
    /// `EXPIRY` events.
    std::optional<std::string> amount;
    /// Only for `EXPIRY` events on short positions (covered call / cash-secured put): collateral
    /// released back to the user, e.g. the cash of a cash-secured put (strike × contracts ×
    /// multiplier).
    std::optional<std::vector<OptionSettlementEventDetailResponseCollateralReleaseInner>>
        collateral_release;
    /// Last update time (ms).
    std::optional<std::int64_t> updated_time;

    bool operator==(const OptionSettlementEventDetailResponse& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionSettlementEventDetailResponse
tag_invoke(boost::json::value_to_tag<OptionSettlementEventDetailResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionSettlementEventDetailResponse& v);

} // namespace binance::stock_options::rest_api
