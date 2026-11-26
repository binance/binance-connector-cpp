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

struct TokenizedMintResponse {
    /// Server-assigned convert request id. Use it to poll `/tokenized/convert-status`.
    std::optional<std::string> issuer_request_id;
    /// Convert status code: `P` = processing, `S` = success, `F` = failed.
    std::optional<std::string> status;
    /// The wallet the tokenized asset is settled in: `MAIN` = Spot wallet, `CARD` = Funding wallet.
    std::optional<std::string> tokenized_asset_settle_wallet_type;

    bool operator==(const TokenizedMintResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TokenizedMintResponse
tag_invoke(boost::json::value_to_tag<TokenizedMintResponse> /*tag*/, const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TokenizedMintResponse& v);

} // namespace binance::stocks::rest_api
