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

#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

struct GetUmFuturesTradeDownloadLinkByIdResponse {
    /// Download ID.
    std::optional<std::string> download_id;
    /// Enum：completed，processing
    std::optional<std::string> status;
    /// The link is mapped to download id
    std::optional<std::string> url;
    /// S3 Link.
    std::optional<std::string> s3_link;
    /// ignore
    std::optional<bool> notified;
    /// The link would expire after this timestamp
    std::optional<std::int64_t> expiration_timestamp;
    /// Is Expired.
    std::optional<std::string> is_expired;

    bool operator==(const GetUmFuturesTradeDownloadLinkByIdResponse& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT GetUmFuturesTradeDownloadLinkByIdResponse
tag_invoke(boost::json::value_to_tag<GetUmFuturesTradeDownloadLinkByIdResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetUmFuturesTradeDownloadLinkByIdResponse& v);

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
