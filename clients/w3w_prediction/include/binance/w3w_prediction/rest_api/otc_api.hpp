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
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/w3w_prediction/export.hpp>
#include <binance/w3w_prediction/rest_api/models/create_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/fulfil_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_detail_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_events_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_assets_parameter_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_otc_blocktrades_response.hpp>
#include <binance/w3w_prediction/rest_api/models/preview_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/remove_otc_blocktrades_response.hpp>

namespace binance::w3w_prediction::rest_api {

enum class CreateOtcBlocktradeSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(CreateOtcBlocktradeSideEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT CreateOtcBlocktradeSideEnum tag_invoke(
    boost::json::value_to_tag<CreateOtcBlocktradeSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              CreateOtcBlocktradeSideEnum value);

enum class ListOtcBlocktradesStatusEnum {
    Open,
    Fulfilled,
    Matched,
    Cancelled,
    Expired,
    Failed,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(ListOtcBlocktradesStatusEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT ListOtcBlocktradesStatusEnum tag_invoke(
    boost::json::value_to_tag<ListOtcBlocktradesStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              ListOtcBlocktradesStatusEnum value);

struct CreateOtcBlocktradeParams {
    /// PredictFun market id
    common::Required<std::string> market_id;
    /// ERC-1155 outcome token id
    common::Required<std::string> token_id;
    /// Trade side. Enum: `BUY` (BID), `SELL` (ASK)
    common::Required<CreateOtcBlocktradeSideEnum> side;
    /// Maker amount in wei. BID：USDT; ASK：shares
    common::Required<std::string> maker_amount;
    /// Taker amount in wei. BID：shares; ASK：USDT
    common::Required<std::string> taker_amount;
    /// Price per share (decimal ether, e.g. `0.65`)
    common::Required<std::string> price_per_share;
    /// Expiration timestamp in seconds (GTD order)
    common::Required<std::int64_t> expiration;
};

struct FulfilOtcBlocktradeParams {
    /// Maker order id (returned by maker create)
    common::Required<std::string> order_id;
    /// One-time fulfilment token the maker shared out-of-band
    common::Required<std::string> secret_token;
};

struct GetOtcBlocktradeDetailParams {
    /// Maker order id (returned by create)
    common::Required<std::string> order_id;
};

struct GetOtcBlocktradeEventsParams {
    /// Page size
    std::optional<std::int64_t> first = std::nullopt;
    /// Pagination cursor
    std::optional<std::string> after = std::nullopt;
    /// Filter by event types (e.g. `["MATCH_SUCCESS","EXPIRE"]`)
    std::optional<std::vector<std::string>> event_types = std::nullopt;
    /// Filter by market id
    std::optional<std::int64_t> market_id = std::nullopt;
};

struct GetOtcReservedBalancesParams {
    /// Assets to query (max 50)
    common::Required<std::vector<GetOtcReservedBalancesAssetsParameterInner>> assets;
};

struct ListOtcBlocktradesParams {
    /// Page size
    std::optional<std::int64_t> first = std::nullopt;
    /// Pagination cursor (from previous response)
    std::optional<std::string> after = std::nullopt;
    /// Filter by status. Enum: `OPEN`, `FULFILLED`, `MATCHED`, `CANCELLED`, `EXPIRED`, `FAILED`
    std::optional<ListOtcBlocktradesStatusEnum> status = std::nullopt;
};

struct PreviewOtcBlocktradeParams {
    /// One-time fulfilment token the maker shared out-of-band
    common::Required<std::string> secret_token;
};

struct RemoveOtcBlocktradesParams {
    /// Order ids to remove (max 100). Must be the `orderId` returned by Create OTC Blocktrade
    common::Required<std::vector<std::string>> order_ids;
};

class BINANCE_W3W_PREDICTION_EXPORT OtcApi {
public:
    explicit OtcApi(std::shared_ptr<common::RestClient> client);

    /// Create OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/create.
    ///
    /// Create an OTC blocktrade as the maker (BID to buy outcome shares with USDT, or ASK to sell
    /// outcome shares for USDT). The maker wallet is resolved server-side by `userId`; signing is
    /// done server-side via SAS `typedDataSign`. Returns `orderId` and a one-time `secretToken` to
    /// share out-of-band with the intended taker.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - Side & Amount Rules:
    ///
    ///   | side   | makerAmount   | takerAmount   |
    ///   | ------ | ------------- | ------------- |
    ///   | `BUY`  | USDT (wei)    | shares (wei)  |
    ///   | `SELL` | shares (wei)  | USDT (wei)    |
    /// - "Note on `side` encoding: this request uses a string enum (`BUY`/`SELL`). Responses from
    /// Get Blocktrade Detail / Preview / List return `side` as an integer and also include a
    /// `quoteType` string — both encode the same concept."
    ///
    ///   | Request `side` | Response `side` (Integer) | Response `quoteType` |
    ///   | --------------- | -------------------------- | ---------------------- |
    ///   | `BUY`           | `0`                         | `"Bid"`                |
    ///   | `SELL`          | `1`                         | `"Ask"`                |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#create-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<CreateOtcBlocktradeResponse>
    create_otc_blocktrade(const CreateOtcBlocktradeParams& params) const;

    /// Asynchronous `create_otc_blocktrade()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateOtcBlocktradeResponse>)`.
    template <class CompletionToken>
    auto async_create_otc_blocktrade(const CreateOtcBlocktradeParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<CreateOtcBlocktradeResponse>(
            client_, create_otc_blocktrade_request(params), std::forward<CompletionToken>(token));
    }

    /// Fulfil OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/fulfil.
    ///
    /// Fulfil an open maker blocktrade as the taker, using the `secretToken` the maker shared
    /// out-of-band. All-or-nothing fill (no partial fill); the taker order is the server-derived
    /// symmetric inverse of the maker order.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#fulfil-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<FulfilOtcBlocktradeResponse>
    fulfil_otc_blocktrade(const FulfilOtcBlocktradeParams& params) const;

    /// Asynchronous `fulfil_otc_blocktrade()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<FulfilOtcBlocktradeResponse>)`.
    template <class CompletionToken>
    auto async_fulfil_otc_blocktrade(const FulfilOtcBlocktradeParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<FulfilOtcBlocktradeResponse>(
            client_, fulfil_otc_blocktrade_request(params), std::forward<CompletionToken>(token));
    }

    /// Get OTC Blocktrade Detail (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/detail.
    ///
    /// Query the maker's own blocktrade by `orderId`. Returns full order data including status and
    /// `secretToken`.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-blocktrade-detail
    [[nodiscard]] common::RestApiResponse<GetOtcBlocktradeDetailResponse>
    get_otc_blocktrade_detail(const GetOtcBlocktradeDetailParams& params) const;

    /// Asynchronous `get_otc_blocktrade_detail()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOtcBlocktradeDetailResponse>)`.
    template <class CompletionToken>
    auto async_get_otc_blocktrade_detail(const GetOtcBlocktradeDetailParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetOtcBlocktradeDetailResponse>(
            client_, get_otc_blocktrade_detail_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get OTC Blocktrade Events (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/events.
    ///
    /// Paginated feed of blocktrade lifecycle and settlement events (CREATE, FULFIL, MATCH_SUBMIT,
    /// MATCH_SUCCESS, EXPIRE, FAILED, etc.).
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-blocktrade-events
    [[nodiscard]] common::RestApiResponse<GetOtcBlocktradeEventsResponse>
    get_otc_blocktrade_events(const GetOtcBlocktradeEventsParams& params = {}) const;

    /// Asynchronous `get_otc_blocktrade_events()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOtcBlocktradeEventsResponse>)`.
    template <class CompletionToken>
    auto async_get_otc_blocktrade_events(const GetOtcBlocktradeEventsParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetOtcBlocktradeEventsResponse>(
            client_, get_otc_blocktrade_events_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get OTC Reserved Balances (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/reserved-balances.
    ///
    /// Query PredictFun reserved balances for the caller's bound wallet — these are funds locked by
    /// the caller's open OTC blocktrade orders (maker BID locks USDT, maker ASK locks shares). Not
    /// tied to a specific blocktrade id; the path nesting under `otc/blocktrade` reflects the cause
    /// of the lock, not a per-order query. Returns one entry per requested asset, aligned with the
    /// request order. Pass `{type:"USDT"}` for reserved USDT, or `{type:"SHARE", tokenId:"..."}`
    /// for a specific outcome token's reserved shares.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    /// - AssetQuery:
    ///
    ///   | Name    | Type   | Mandatory | Description |
    ///   | ------- | ------ | --------- | ----------- |
    ///   | type    | STRING | YES       | Asset type. Enum: `USDT`, `SHARE` |
    ///   | tokenId | STRING | NO        | Outcome token id (present for `SHARE` entries only) |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#get-otc-reserved-balances
    [[nodiscard]] common::RestApiResponse<GetOtcReservedBalancesResponse>
    get_otc_reserved_balances(const GetOtcReservedBalancesParams& params) const;

    /// Asynchronous `get_otc_reserved_balances()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetOtcReservedBalancesResponse>)`.
    template <class CompletionToken>
    auto async_get_otc_reserved_balances(const GetOtcReservedBalancesParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<GetOtcReservedBalancesResponse>(
            client_, get_otc_reserved_balances_request(params),
            std::forward<CompletionToken>(token));
    }

    /// List OTC Blocktrades (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/list.
    ///
    /// List the maker's own blocktrades with optional status filter and cursor pagination.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#list-otc-blocktrades
    [[nodiscard]] common::RestApiResponse<ListOtcBlocktradesResponse>
    list_otc_blocktrades(const ListOtcBlocktradesParams& params = {}) const;

    /// Asynchronous `list_otc_blocktrades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ListOtcBlocktradesResponse>)`.
    template <class CompletionToken>
    auto async_list_otc_blocktrades(const ListOtcBlocktradesParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<ListOtcBlocktradesResponse>(
            client_, list_otc_blocktrades_request(params), std::forward<CompletionToken>(token));
    }

    /// Preview OTC Blocktrade (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/preview.
    ///
    /// Inspect an open blocktrade by `secretToken` (no `orderId` needed). Taker uses this to
    /// preview the maker order before fulfilling. Returns the same shape as `Get Blocktrade
    /// Detail`, but `orderId` is `null` and `secretToken` is never returned from this endpoint.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#preview-otc-blocktrade
    [[nodiscard]] common::RestApiResponse<PreviewOtcBlocktradeResponse>
    preview_otc_blocktrade(const PreviewOtcBlocktradeParams& params) const;

    /// Asynchronous `preview_otc_blocktrade()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<PreviewOtcBlocktradeResponse>)`.
    template <class CompletionToken>
    auto async_preview_otc_blocktrade(const PreviewOtcBlocktradeParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<PreviewOtcBlocktradeResponse>(
            client_, preview_otc_blocktrade_request(params), std::forward<CompletionToken>(token));
    }

    /// Remove OTC Blocktrades (PREDICTION_TRADE)
    ///
    /// POST /sapi/v1/w3w/wallet/prediction/otc/blocktrade/remove.
    ///
    /// Cancel open or fulfilled-but-unsettled blocktrades. Terminal orders (already
    /// `MATCHED`/`CANCELLED`/`EXPIRED`/`FAILED`) are returned in `noop` instead of `removed`.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: PREDICTION_TRADE
    ///
    /// Notes:
    /// - Restricted to authorized market makers. Requests from unauthorized accounts are rejected —
    /// contact BD to request access.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/web3-wallet-prediction-trading/api/rest-api/otc#remove-otc-blocktrades
    [[nodiscard]] common::RestApiResponse<RemoveOtcBlocktradesResponse>
    remove_otc_blocktrades(const RemoveOtcBlocktradesParams& params) const;

    /// Asynchronous `remove_otc_blocktrades()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RemoveOtcBlocktradesResponse>)`.
    template <class CompletionToken>
    auto async_remove_otc_blocktrades(const RemoveOtcBlocktradesParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<RemoveOtcBlocktradesResponse>(
            client_, remove_otc_blocktrades_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_otc_blocktrade_request(const CreateOtcBlocktradeParams& params) const;
    [[nodiscard]] common::RestRequest
    fulfil_otc_blocktrade_request(const FulfilOtcBlocktradeParams& params) const;
    [[nodiscard]] common::RestRequest
    get_otc_blocktrade_detail_request(const GetOtcBlocktradeDetailParams& params) const;
    [[nodiscard]] common::RestRequest
    get_otc_blocktrade_events_request(const GetOtcBlocktradeEventsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_otc_reserved_balances_request(const GetOtcReservedBalancesParams& params) const;
    [[nodiscard]] common::RestRequest
    list_otc_blocktrades_request(const ListOtcBlocktradesParams& params) const;
    [[nodiscard]] common::RestRequest
    preview_otc_blocktrade_request(const PreviewOtcBlocktradeParams& params) const;
    [[nodiscard]] common::RestRequest
    remove_otc_blocktrades_request(const RemoveOtcBlocktradesParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::w3w_prediction::rest_api
