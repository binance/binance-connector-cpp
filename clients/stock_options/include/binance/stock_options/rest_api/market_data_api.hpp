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
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/option_contracts_response_inner.hpp>
#include <binance/stock_options/rest_api/models/option_exchange_info_response.hpp>
#include <binance/stock_options/rest_api/models/option_expirations_response_inner.hpp>

namespace binance::stock_options::rest_api {

struct OptionContractsParams {
    /// Underlying US-equity ticker, e.g. `NVDA`.
    common::Required<std::string> underlying_symbol;
    /// Expiration date in `YYYY-MM-DD`, taken from Option Expirations. Other formats (e.g.
    /// `2026-9-30`, `2026/09/30`) are rejected.
    common::Required<std::string> expiration_date;
    /// OCC root. If omitted, only **standard** contracts are returned. To list
    /// corporate-action-adjusted contracts (e.g. `GOOG1`), pass the `rootSymbol` from Option
    /// Expirations.
    std::optional<std::string> root_symbol = std::nullopt;
};

struct OptionExchangeInfoParams {
    /// OCC contract symbol, e.g. `NVDA260930C00100000`.
    common::Required<std::string> symbol;
};

struct OptionExpirationsParams {
    /// Underlying US-equity ticker, e.g. `NVDA`.
    common::Required<std::string> underlying_symbol;
};

class BINANCE_STOCK_OPTIONS_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Option Contracts (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/contracts.
    ///
    /// Returns every option contract (calls and puts) of an underlying for one expiration date.
    /// Reference data only — no market data.
    ///
    /// Sorted by `strikePrice` ascending; for the same strike, `CALL` comes before `PUT`. Not
    /// paginated.
    ///
    /// If there is no contract for the `(underlying, root, expiration)` combination, an empty array
    /// is returned.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-contracts
    [[nodiscard]] common::RestApiResponse<std::vector<OptionContractsResponseInner>>
    option_contracts(const OptionContractsParams& params) const;

    /// Asynchronous `option_contracts()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OptionContractsResponseInner>>)`.
    template <class CompletionToken>
    auto async_option_contracts(const OptionContractsParams& params,
                                CompletionToken&& token) const {
        return common::async_send<std::vector<OptionContractsResponseInner>>(
            client_, option_contracts_request(params), std::forward<CompletionToken>(token));
    }

    /// Option Exchange Info (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/exchangeInfo.
    ///
    /// Returns the trading rules of a single option contract, combining contract-level data (type,
    /// strike, expiration, multiplier, deliverables) with underlying-level configuration (price /
    /// quantity increments and limits).
    ///
    /// `symbol` is **required**. Unlike the stock `exchangeInfo`, listing all contracts is not
    /// supported. To browse contracts, use Option Expirations and Option Contracts.
    ///
    /// **Price constraints**: a limit price must be a multiple of `tickSize`, and the order
    /// notional (`price` × `quantity` × `multiplier`, excluding fees) must fall within the closed
    /// interval `[minNotional, maxNotional]`. For a put `SELL` order, the limit price cannot exceed
    /// the strike price. All of these values are returned by this endpoint, so you can validate an
    /// order before placing it.
    ///
    /// **`multiplier` vs `contractSize`**: `multiplier` is used to calculate cost, `contractSize`
    /// is the number of shares delivered. Both are 100 for standard contracts and may differ for
    /// contracts adjusted by a corporate action (split, merger, special dividend). Always estimate
    /// cost with `multiplier`.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-exchange-info
    [[nodiscard]] common::RestApiResponse<OptionExchangeInfoResponse>
    option_exchange_info(const OptionExchangeInfoParams& params) const;

    /// Asynchronous `option_exchange_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OptionExchangeInfoResponse>)`.
    template <class CompletionToken>
    auto async_option_exchange_info(const OptionExchangeInfoParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<OptionExchangeInfoResponse>(
            client_, option_exchange_info_request(params), std::forward<CompletionToken>(token));
    }

    /// Option Expirations (MARKET_DATA)
    ///
    /// GET /sapi/v1/equity/option/market/expirations.
    ///
    /// Returns every expiration date currently tradable for an underlying, in ascending
    /// `expirationDate` order.
    ///
    /// When standard and corporate-action-adjusted contracts share an expiration date, **multiple**
    /// rows are returned with the same `expirationDate` and different `rootSymbol`. To list the
    /// adjusted set, pass that `rootSymbol` to Option Contracts.
    ///
    /// Reference data only — no market data.
    ///
    /// An unknown underlying, or one without listed options, returns `-1121 Invalid symbol.` An
    /// empty array is never returned.
    ///
    /// Only the `X-MBX-APIKEY` header is required; this endpoint is **not signed** and takes no
    /// `timestamp` / `recvWindow`.
    ///
    /// Weight: 1
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/market-data#option-expirations
    [[nodiscard]] common::RestApiResponse<std::vector<OptionExpirationsResponseInner>>
    option_expirations(const OptionExpirationsParams& params) const;

    /// Asynchronous `option_expirations()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OptionExpirationsResponseInner>>)`.
    template <class CompletionToken>
    auto async_option_expirations(const OptionExpirationsParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<OptionExpirationsResponseInner>>(
            client_, option_expirations_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    option_contracts_request(const OptionContractsParams& params) const;
    [[nodiscard]] common::RestRequest
    option_exchange_info_request(const OptionExchangeInfoParams& params) const;
    [[nodiscard]] common::RestRequest
    option_expirations_request(const OptionExpirationsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stock_options::rest_api
