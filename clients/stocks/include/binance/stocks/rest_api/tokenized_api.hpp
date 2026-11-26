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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/bstocks_corporate_action_records_response.hpp>
#include <binance/stocks/rest_api/models/corporate_action_records_response.hpp>
#include <binance/stocks/rest_api/models/tokenized_convert_history_response.hpp>
#include <binance/stocks/rest_api/models/tokenized_convert_status_response.hpp>
#include <binance/stocks/rest_api/models/tokenized_mint_response.hpp>
#include <binance/stocks/rest_api/models/tokenized_redeem_response.hpp>

namespace binance::stocks::rest_api {

enum class TokenizedConvertStatusConvertTypeEnum {
    Mint,
    Redeem,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(TokenizedConvertStatusConvertTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT TokenizedConvertStatusConvertTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedConvertStatusConvertTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      TokenizedConvertStatusConvertTypeEnum value);

enum class TokenizedMintTokenizedAssetSettleWalletTypeEnum {
    Main,
    Card,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(TokenizedMintTokenizedAssetSettleWalletTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT TokenizedMintTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedMintTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      TokenizedMintTokenizedAssetSettleWalletTypeEnum value);

enum class TokenizedRedeemTokenizedAssetSettleWalletTypeEnum {
    Main,
    Card,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_STOCKS_EXPORT std::string_view
to_string(TokenizedRedeemTokenizedAssetSettleWalletTypeEnum value) noexcept;
BINANCE_STOCKS_EXPORT TokenizedRedeemTokenizedAssetSettleWalletTypeEnum
tag_invoke(boost::json::value_to_tag<TokenizedRedeemTokenizedAssetSettleWalletTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      TokenizedRedeemTokenizedAssetSettleWalletTypeEnum value);

struct BstocksCorporateActionRecordsParams {
    /// Number of records to return. Default `20`, range `1` to `100`.
    common::Required<std::int64_t> limit;
    /// The `nextTime` returned by the previous page, in milliseconds. Must be sent together with
    /// `lastId`.
    std::optional<std::int64_t> last_time = std::nullopt;
    /// The `nextId` returned by the previous page. Must be sent together with `lastTime`.
    std::optional<std::int64_t> last_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CorporateActionRecordsParams {
    /// Number of records to return. Default `20`, range `1` to `100`.
    common::Required<std::int64_t> limit;
    /// The `nextTime` returned by the previous page, in milliseconds. Must be sent together with
    /// `lastId`.
    std::optional<std::int64_t> last_time = std::nullopt;
    /// The `nextId` returned by the previous page. Must be sent together with `lastTime`.
    std::optional<std::int64_t> last_id = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TokenizedConvertHistoryParams {
    /// Start time (ms epoch).
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time (ms epoch).
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Last record id from the previous page. Omit (or leave unset) to fetch the first page.
    std::optional<std::int64_t> last_id = std::nullopt;
    /// Page size. Default `20`, max `100`.
    std::optional<std::int64_t> size = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TokenizedConvertStatusParams {
    /// Convert request id returned by `/tokenized/mint` or `/redeem`.
    common::Required<std::string> issuer_request_id;
    /// `MINT` or `REDEEM`.
    common::Required<TokenizedConvertStatusConvertTypeEnum> convert_type;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TokenizedMintParams {
    /// Underlying US-equity ticker, e.g. `AAPL`, `TSLA`. Resolved against the active-symbol list;
    /// unknown tickers return `-26004`. The target tokenized asset is looked up from this field via
    /// `/market/tokenized-assets`.
    common::Required<std::string> underlying_asset;
    /// Quantity of the underlying asset to mint from. Must be > 0.
    common::Required<std::string> underlying_asset_amount;
    /// Client order id for idempotency. Format `^[a-zA-Z0-9-_]{32,36}$`. Auto-generated when
    /// omitted.
    std::optional<std::string> client_order_id = std::nullopt;
    /// Wallet that receives the minted tokenized asset. `MAIN` = Spot wallet, `CARD` = Funding
    /// wallet. Default `CARD`. If `MAIN` is sent while Spot wallet settlement is not enabled, the
    /// request is rejected as an illegal parameter.
    std::optional<TokenizedMintTokenizedAssetSettleWalletTypeEnum>
        tokenized_asset_settle_wallet_type = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TokenizedRedeemParams {
    /// Tokenized asset to redeem, e.g. `AAPLB`. Not a US-equity ticker — this is the on-chain
    /// tokenized asset identifier. Unknown asset returns `-1102` (the message currently says the
    /// parameter was empty/malformed, but it was in fact sent — it is simply unknown). The target
    /// underlying ticker is looked up from this field via `/market/tokenized-assets`.
    common::Required<std::string> tokenized_asset;
    /// Quantity of the tokenized asset to redeem. Must be > 0.
    common::Required<std::string> tokenized_asset_amount;
    /// Client order id for idempotency. Format `^[a-zA-Z0-9-_]{32,36}$`. Auto-generated when
    /// omitted.
    std::optional<std::string> client_order_id = std::nullopt;
    /// Wallet the tokenized asset is deducted from on redeem. `MAIN` = Spot wallet, `CARD` =
    /// Funding wallet. Default `CARD`. If `MAIN` is sent while Spot wallet settlement is not
    /// enabled, the request is rejected as an illegal parameter.
    std::optional<TokenizedRedeemTokenizedAssetSettleWalletTypeEnum>
        tokenized_asset_settle_wallet_type = std::nullopt;
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCKS_EXPORT TokenizedApi {
public:
    explicit TokenizedApi(std::shared_ptr<common::RestClient> client);

    /// Bstocks Corporate Action Records (USER_DATA)
    ///
    /// GET /sapi/v1/bstocks/corp-action.
    ///
    /// Query the asset balance changes caused by corporate actions (for example stock splits and
    /// cash dividends) on the caller's account. Cursor-style pagination — supply the `nextTime` and
    /// `nextId` from the previous page's response as `lastTime` and `lastId` to fetch the next
    /// page. Records are returned in descending order of modification time. This endpoint is
    /// equivalent to `/sapi/v1/equity/corp-action`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#bstocks-corporate-action-records
    [[nodiscard]] common::RestApiResponse<BstocksCorporateActionRecordsResponse>
    bstocks_corporate_action_records(const BstocksCorporateActionRecordsParams& params) const;

    /// Asynchronous `bstocks_corporate_action_records()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<BstocksCorporateActionRecordsResponse>)`.
    template <class CompletionToken>
    auto async_bstocks_corporate_action_records(const BstocksCorporateActionRecordsParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<BstocksCorporateActionRecordsResponse>(
            client_, bstocks_corporate_action_records_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Corporate Action Records (USER_DATA)
    ///
    /// GET /sapi/v1/equity/corp-action.
    ///
    /// Query the asset balance changes caused by corporate actions (for example stock splits and
    /// cash dividends) on the caller's account. Cursor-style pagination — supply the `nextTime` and
    /// `nextId` from the previous page's response as `lastTime` and `lastId` to fetch the next
    /// page. Records are returned in descending order of modification time. This endpoint is
    /// equivalent to `/sapi/v1/bstocks/corp-action`.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#corporate-action-records
    [[nodiscard]] common::RestApiResponse<CorporateActionRecordsResponse>
    corporate_action_records(const CorporateActionRecordsParams& params) const;

    /// Asynchronous `corporate_action_records()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CorporateActionRecordsResponse>)`.
    template <class CompletionToken>
    auto async_corporate_action_records(const CorporateActionRecordsParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<CorporateActionRecordsResponse>(
            client_, corporate_action_records_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Tokenized Convert History (USER_DATA)
    ///
    /// GET /sapi/v1/equity/tokenized/history.
    ///
    /// Paged history of mint / redeem conversions for the caller. Cursor-style pagination — supply
    /// the `nextLastId` from the previous page's response to fetch the next page.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-convert-history
    [[nodiscard]] common::RestApiResponse<TokenizedConvertHistoryResponse>
    tokenized_convert_history(const TokenizedConvertHistoryParams& params = {}) const;

    /// Asynchronous `tokenized_convert_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TokenizedConvertHistoryResponse>)`.
    template <class CompletionToken>
    auto async_tokenized_convert_history(const TokenizedConvertHistoryParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<TokenizedConvertHistoryResponse>(
            client_, tokenized_convert_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Tokenized Convert Status (USER_DATA)
    ///
    /// GET /sapi/v1/equity/tokenized/convert-status.
    ///
    /// Query the current status of a single mint / redeem request by its `issuerRequestId`. Returns
    /// an empty object when no record matches (caller's ID scope only).
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-convert-status
    [[nodiscard]] common::RestApiResponse<TokenizedConvertStatusResponse>
    tokenized_convert_status(const TokenizedConvertStatusParams& params) const;

    /// Asynchronous `tokenized_convert_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TokenizedConvertStatusResponse>)`.
    template <class CompletionToken>
    auto async_tokenized_convert_status(const TokenizedConvertStatusParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<TokenizedConvertStatusResponse>(
            client_, tokenized_convert_status_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Tokenized Mint (TRADE)
    ///
    /// POST /sapi/v1/equity/tokenized/mint.
    ///
    /// Mint a tokenized asset from an underlying equity holding. The caller's underlying equity
    /// (e.g. `AAPL`) is burned (or locked), and the corresponding tokenized asset (e.g. `AAPLB`) is
    /// credited. The tokenized asset is resolved server-side from `underlyingAsset`; callers only
    /// provide the underlying ticker and quantity. Mint is asynchronous: the endpoint returns an
    /// `issuerRequestId` immediately with a transient status; poll `/tokenized/convert-status` to
    /// observe the terminal state, or inspect `/tokenized/history` for the full record. Rate limit:
    /// 50 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-mint
    [[nodiscard]] common::RestApiResponse<TokenizedMintResponse>
    tokenized_mint(const TokenizedMintParams& params) const;

    /// Asynchronous `tokenized_mint()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TokenizedMintResponse>)`.
    template <class CompletionToken>
    auto async_tokenized_mint(const TokenizedMintParams& params, CompletionToken&& token) const {
        return common::async_send<TokenizedMintResponse>(client_, tokenized_mint_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// Tokenized Redeem (TRADE)
    ///
    /// POST /sapi/v1/equity/tokenized/redeem.
    ///
    /// Redeem a tokenized asset back into the underlying equity. The caller's tokenized asset (e.g.
    /// `AAPLB`) is burned, and the corresponding underlying equity (e.g. `AAPL`) is released. The
    /// underlying asset is resolved server-side from `tokenizedAsset`; callers only provide the
    /// tokenized asset and quantity. Redeem is asynchronous: the endpoint returns an
    /// `issuerRequestId` immediately with a transient status; poll `/tokenized/convert-status` to
    /// observe the terminal state, or inspect `/tokenized/history` for the full record. Rate limit:
    /// 200 requests / min (UID).
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/tokenized#tokenized-redeem
    [[nodiscard]] common::RestApiResponse<TokenizedRedeemResponse>
    tokenized_redeem(const TokenizedRedeemParams& params) const;

    /// Asynchronous `tokenized_redeem()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TokenizedRedeemResponse>)`.
    template <class CompletionToken>
    auto async_tokenized_redeem(const TokenizedRedeemParams& params,
                                CompletionToken&& token) const {
        return common::async_send<TokenizedRedeemResponse>(
            client_, tokenized_redeem_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest bstocks_corporate_action_records_request(
        const BstocksCorporateActionRecordsParams& params) const;
    [[nodiscard]] common::RestRequest
    corporate_action_records_request(const CorporateActionRecordsParams& params) const;
    [[nodiscard]] common::RestRequest
    tokenized_convert_history_request(const TokenizedConvertHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    tokenized_convert_status_request(const TokenizedConvertStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    tokenized_mint_request(const TokenizedMintParams& params) const;
    [[nodiscard]] common::RestRequest
    tokenized_redeem_request(const TokenizedRedeemParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stocks::rest_api
