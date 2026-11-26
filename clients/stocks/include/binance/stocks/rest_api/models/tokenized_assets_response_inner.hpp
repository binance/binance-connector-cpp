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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/stocks/export.hpp>

namespace binance::stocks::rest_api {

struct TokenizedAssetsResponseInner {
    /// Tokenized asset code, e.g. `AAPLB`.
    std::optional<std::string> asset_code;
    /// Human-readable display name of the tokenized asset.
    std::optional<std::string> asset_name;
    /// Underlying US-equity ticker, e.g. `AAPL`. Use this when calling `/tokenized/mint` or
    /// `/tokenized/redeem`.
    std::optional<std::string> underlying_equity_symbol;
    /// Conversion multiplier between the underlying equity and the tokenized asset.
    std::optional<std::string> multiplier;
    /// Whether the multiplier is currently valid and applicable.
    std::optional<bool> multiplier_valid;

    bool operator==(const TokenizedAssetsResponseInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TokenizedAssetsResponseInner tag_invoke(
    boost::json::value_to_tag<TokenizedAssetsResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TokenizedAssetsResponseInner& v);

} // namespace binance::stocks::rest_api
