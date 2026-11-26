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

struct TokenizedConvertHistoryResponseRowsInner {
    /// Underlying US-equity ticker, e.g. `AAPL`.
    std::optional<std::string> underlying_asset;
    /// Quantity of the underlying asset involved.
    std::optional<std::string> underlying_asset_amount;
    /// Tokenized asset, e.g. `AAPLB`.
    std::optional<std::string> tokenized_asset;
    /// Quantity of the tokenized asset involved.
    std::optional<std::string> tokenized_asset_amount;
    /// Convert request id.
    std::optional<std::string> issuer_request_id;
    /// `MINT` or `REDEEM`.
    std::optional<std::string> convert_type;
    /// Convert status: `P` = processing, `S` = success, `F` = failed.
    std::optional<std::string> status;
    /// Creation time (ms epoch).
    std::optional<std::int64_t> created_at;
    /// Last update time (ms epoch).
    std::optional<std::int64_t> updated_at;
    /// The wallet the tokenized asset is settled in: `MAIN` = Spot wallet, `CARD` = Funding wallet.
    std::optional<std::string> tokenized_asset_settle_wallet_type;

    bool operator==(const TokenizedConvertHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TokenizedConvertHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<TokenizedConvertHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TokenizedConvertHistoryResponseRowsInner& v);

} // namespace binance::stocks::rest_api
