//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/copy_trading/export.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trader_status_response.hpp>
#include <binance/copy_trading/rest_api/models/get_futures_lead_trading_symbol_whitelist_response.hpp>

namespace binance::copy_trading::rest_api {

struct GetFuturesLeadTraderStatusParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetFuturesLeadTradingSymbolWhitelistParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_COPY_TRADING_EXPORT FutureCopyTradingApi {
public:
    explicit FutureCopyTradingApi(std::shared_ptr<common::RestClient> client);

    /// Get Futures Lead Trader Status (TRADE)
    ///
    /// GET /sapi/v1/copyTrading/futures/userStatus.
    ///
    /// Get Futures Lead Trader Status
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-copy-trading/api/rest-api/future-copy-trading#get-futures-lead-trader-status
    [[nodiscard]] common::RestApiResponse<GetFuturesLeadTraderStatusResponse>
    get_futures_lead_trader_status(const GetFuturesLeadTraderStatusParams& params = {}) const;

    /// Asynchronous `get_futures_lead_trader_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetFuturesLeadTraderStatusResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_lead_trader_status(const GetFuturesLeadTraderStatusParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<GetFuturesLeadTraderStatusResponse>(
            client_, get_futures_lead_trader_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Futures Lead Trading Symbol Whitelist (USER_DATA)
    ///
    /// GET /sapi/v1/copyTrading/futures/leadSymbol.
    ///
    /// Get Futures Lead Trading Symbol Whitelist
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-copy-trading/api/rest-api/future-copy-trading#get-futures-lead-trading-symbol-whitelist
    [[nodiscard]] common::RestApiResponse<GetFuturesLeadTradingSymbolWhitelistResponse>
    get_futures_lead_trading_symbol_whitelist(
        const GetFuturesLeadTradingSymbolWhitelistParams& params = {}) const;

    /// Asynchronous `get_futures_lead_trading_symbol_whitelist()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<GetFuturesLeadTradingSymbolWhitelistResponse>)`.
    template <class CompletionToken>
    auto async_get_futures_lead_trading_symbol_whitelist(
        const GetFuturesLeadTradingSymbolWhitelistParams& params, CompletionToken&& token) const {
        return common::async_send<GetFuturesLeadTradingSymbolWhitelistResponse>(
            client_, get_futures_lead_trading_symbol_whitelist_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_futures_lead_trader_status_request(const GetFuturesLeadTraderStatusParams& params) const;
    [[nodiscard]] common::RestRequest get_futures_lead_trading_symbol_whitelist_request(
        const GetFuturesLeadTradingSymbolWhitelistParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::copy_trading::rest_api
