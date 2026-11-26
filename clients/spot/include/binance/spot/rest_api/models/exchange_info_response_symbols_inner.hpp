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

#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/my_filters_response_symbol_filters_inner.hpp>

namespace binance::spot::rest_api {

struct ExchangeInfoResponseSymbolsInner {
    std::optional<std::string> symbol;
    std::optional<std::string> status;
    std::optional<std::string> base_asset;
    std::optional<std::int64_t> base_asset_precision;
    std::optional<std::string> quote_asset;
    /// will be removed in future api versions (v4+)
    std::optional<std::int64_t> quote_precision;
    std::optional<std::int64_t> quote_asset_precision;
    std::optional<std::int64_t> base_commission_precision;
    std::optional<std::int64_t> quote_commission_precision;
    std::optional<std::vector<std::string>> order_types;
    std::optional<bool> iceberg_allowed;
    std::optional<bool> oco_allowed;
    std::optional<bool> oto_allowed;
    std::optional<bool> opo_allowed;
    std::optional<bool> quote_order_qty_market_allowed;
    std::optional<bool> allow_trailing_stop;
    std::optional<bool> cancel_replace_allowed;
    std::optional<bool> amend_allowed;
    std::optional<bool> peg_instructions_allowed;
    std::optional<bool> market_quote_notional_limit_allowed;
    std::optional<bool> limit_quote_notional_limit_allowed;
    std::optional<bool> is_spot_trading_allowed;
    std::optional<bool> is_margin_trading_allowed;
    /// Symbol filters are explained on the "Filters" page: All symbol filters are optional.
    std::optional<std::vector<MyFiltersResponseSymbolFiltersInner>> filters;
    std::optional<std::vector<std::string>> permissions;
    std::optional<std::vector<std::vector<std::string>>> permission_sets;
    std::optional<std::string> default_self_trade_prevention_mode;
    std::optional<std::vector<std::string>> allowed_self_trade_prevention_modes;

    bool operator==(const ExchangeInfoResponseSymbolsInner& /*other*/) const = default;
};

BINANCE_SPOT_EXPORT ExchangeInfoResponseSymbolsInner
tag_invoke(boost::json::value_to_tag<ExchangeInfoResponseSymbolsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const ExchangeInfoResponseSymbolsInner& v);

} // namespace binance::spot::rest_api
