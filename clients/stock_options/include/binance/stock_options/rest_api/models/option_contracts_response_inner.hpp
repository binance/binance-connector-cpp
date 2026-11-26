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

#include <binance/stock_options/export.hpp>

namespace binance::stock_options::rest_api {

struct OptionContractsResponseInner {
    /// OCC contract symbol; usable for order placement and Option Exchange Info.
    std::optional<std::string> symbol;
    /// `CALL` / `PUT`.
    std::optional<std::string> contract_type;
    /// Strike price.
    std::optional<std::string> strike_price;
    /// Premium multiplier. Order cost = price × quantity × multiplier.
    std::optional<std::string> multiplier;
    /// Shares delivered per contract. Equals `multiplier` for standard contracts; may differ after
    /// a corporate action.
    std::optional<std::int64_t> contract_size;
    /// Expiration date in `YYYY-MM-DD`, US Eastern (ET) calendar day.
    std::optional<std::string> expiration_date;
    /// Contract trading status: `OPEN_CLOSE` / `CLOSE_ONLY` / `NONE`. Omitted when the status of a
    /// contract is temporarily unavailable. See Common Definition.
    std::optional<std::string> status;

    bool operator==(const OptionContractsResponseInner& /*other*/) const = default;
};

BINANCE_STOCK_OPTIONS_EXPORT OptionContractsResponseInner tag_invoke(
    boost::json::value_to_tag<OptionContractsResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_STOCK_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                             boost::json::value& jv,
                                             const OptionContractsResponseInner& v);

} // namespace binance::stock_options::rest_api
