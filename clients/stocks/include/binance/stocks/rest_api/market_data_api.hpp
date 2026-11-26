//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/exchange_info_response.hpp>
#include <binance/stocks/rest_api/models/latest_quote_response.hpp>
#include <binance/stocks/rest_api/models/tokenized_assets_response_inner.hpp>

namespace binance::stocks::rest_api {

struct ExchangeInfoParams {
    /// Filter to a single US-equity ticker, e.g. `AAPL`. When omitted, returns all active symbols.
    /// An unknown ticker returns an empty `symbols` array (HTTP 200), not an error.
    std::optional<std::string> symbol = std::nullopt;
};

struct LatestQuoteParams {
    /// US-equity ticker, e.g. `AAPL`, `TSLA`. Case-insensitive; uppercased server-side.
    common::Required<std::string> symbol;
};

class BINANCE_STOCKS_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Exchange Info (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/exchangeInfo.
    ///
    /// Returns current exchange trading rules and the list of tradable US-equity symbols.
    /// MARKET_DATA endpoint — requires an API key (`X-MBX-APIKEY`) but no signature. Response is
    /// served from a server-side cache.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#exchange-info
    [[nodiscard]] common::RestApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const;

    /// Asynchronous `exchange_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExchangeInfoResponse>)`.
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return common::async_send<ExchangeInfoResponse>(client_, exchange_info_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Latest Quote (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/quote.
    ///
    /// Returns the latest best bid / best ask for a single US-equity ticker. The returned value is
    /// at most ~5 seconds stale. Returns an **empty response body** (not the literal `null`) when
    /// no quote is available for the supplied ticker (e.g. the ticker is unknown, halted, or
    /// de-listed).
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#latest-quote
    [[nodiscard]] common::RestApiResponse<LatestQuoteResponse>
    latest_quote(const LatestQuoteParams& params) const;

    /// Asynchronous `latest_quote()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<LatestQuoteResponse>)`.
    template <class CompletionToken>
    auto async_latest_quote(const LatestQuoteParams& params, CompletionToken&& token) const {
        return common::async_send<LatestQuoteResponse>(client_, latest_quote_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Tokenized Assets (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/market/tokenized-assets.
    ///
    /// Returns the list of all tokenized assets currently available for mint / redeem, together
    /// with each asset's underlying equity symbol and conversion multiplier. MARKET_DATA endpoint —
    /// requires an API key (`X-MBX-APIKEY`) but no signature. Response is served from a server-side
    /// cache.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/market-data#tokenized-assets
    [[nodiscard]] common::RestApiResponse<std::vector<TokenizedAssetsResponseInner>>
    tokenized_assets() const;

    /// Asynchronous `tokenized_assets()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<TokenizedAssetsResponseInner>>)`.
    template <class CompletionToken> auto async_tokenized_assets(CompletionToken&& token) const {
        return common::async_send<std::vector<TokenizedAssetsResponseInner>>(
            client_, tokenized_assets_request(), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest exchange_info_request(const ExchangeInfoParams& params) const;
    [[nodiscard]] common::RestRequest latest_quote_request(const LatestQuoteParams& params) const;
    [[nodiscard]] common::RestRequest tokenized_assets_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stocks::rest_api
