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
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/accept_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/extend_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_legs_parameter_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_details_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_order_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class NewBlockTradeOrderLiquidityEnum {
    Maker,
    Taker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewBlockTradeOrderLiquidityEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewBlockTradeOrderLiquidityEnum
tag_invoke(boost::json::value_to_tag<NewBlockTradeOrderLiquidityEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           NewBlockTradeOrderLiquidityEnum value);

struct AcceptBlockTradeOrderParams {
    common::Required<std::string> block_order_matching_key;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryBlockTradeDetailsParams {
    /// Block trade matching key.
    common::Required<std::string> block_order_matching_key;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AccountBlockTradeListParams {
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Underlying asset.
    std::optional<std::string> underlying = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelBlockTradeOrderParams {
    /// Block trade matching key.
    common::Required<std::string> block_order_matching_key;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ExtendBlockTradeOrderParams {
    common::Required<std::string> block_order_matching_key;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewBlockTradeOrderParams {
    common::Required<NewBlockTradeOrderLiquidityEnum> liquidity;
    /// Max 1 (only single leg supported), list of legs parameters in JSON; example:
    /// eapi/v1/block/order/create?orders=[{"symbol":"BTC-210115-35000-C",
    /// "price":"100","quantity":"0.0002","side":"BUY","type":"LIMIT"}]
    common::Required<std::vector<NewBlockTradeOrderLegsParameterInner>> legs;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryBlockTradeOrderParams {
    /// If specified, returns the specific block trade associated with the blockOrderMatchingKey
    std::optional<std::string> block_order_matching_key = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Underlying asset.
    std::optional<std::string> underlying = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT MarketMakerBlockTradeApi {
public:
    explicit MarketMakerBlockTradeApi(std::shared_ptr<common::RestClient> client);

    /// Accept Block Trade Order (TRADE)
    ///
    /// POST /eapi/v1/block/order/execute.
    ///
    /// Accept a block trade order
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#accept-block-trade-order
    [[nodiscard]] common::RestApiResponse<AcceptBlockTradeOrderResponse>
    accept_block_trade_order(const AcceptBlockTradeOrderParams& params) const;

    /// Asynchronous `accept_block_trade_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AcceptBlockTradeOrderResponse>)`.
    template <class CompletionToken>
    auto async_accept_block_trade_order(const AcceptBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<AcceptBlockTradeOrderResponse>(
            client_, accept_block_trade_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Block Trade Details (USER_DATA)
    ///
    /// GET /eapi/v1/block/order/execute.
    ///
    /// Query block trade details; returns block trade details from counterparty's perspective.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#query-block-trade-details
    [[nodiscard]] common::RestApiResponse<QueryBlockTradeDetailsResponse>
    query_block_trade_details(const QueryBlockTradeDetailsParams& params) const;

    /// Asynchronous `query_block_trade_details()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryBlockTradeDetailsResponse>)`.
    template <class CompletionToken>
    auto async_query_block_trade_details(const QueryBlockTradeDetailsParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<QueryBlockTradeDetailsResponse>(
            client_, query_block_trade_details_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Account Block Trade List (USER_DATA)
    ///
    /// GET /eapi/v1/block/user-trades.
    ///
    /// Gets block trades for a specific account.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#account-block-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountBlockTradeListResponseInner>>
    account_block_trade_list(const AccountBlockTradeListParams& params = {}) const;

    /// Asynchronous `account_block_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AccountBlockTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_account_block_trade_list(const AccountBlockTradeListParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<AccountBlockTradeListResponseInner>>(
            client_, account_block_trade_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Block Trade Order (TRADE)
    ///
    /// DELETE /eapi/v1/block/order/create.
    ///
    /// Cancel a block trade order.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#cancel-block-trade-order
    [[nodiscard]] common::RestApiResponse<boost::json::value>
    cancel_block_trade_order(const CancelBlockTradeOrderParams& params) const;

    /// Asynchronous `cancel_block_trade_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_cancel_block_trade_order(const CancelBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_,
                                                      cancel_block_trade_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Extend Block Trade Order (TRADE)
    ///
    /// PUT /eapi/v1/block/order/create.
    ///
    /// Extends a block trade expire time by 30 mins from the current time.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#extend-block-trade-order
    [[nodiscard]] common::RestApiResponse<ExtendBlockTradeOrderResponse>
    extend_block_trade_order(const ExtendBlockTradeOrderParams& params) const;

    /// Asynchronous `extend_block_trade_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExtendBlockTradeOrderResponse>)`.
    template <class CompletionToken>
    auto async_extend_block_trade_order(const ExtendBlockTradeOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<ExtendBlockTradeOrderResponse>(
            client_, extend_block_trade_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// New Block Trade Order (TRADE)
    ///
    /// POST /eapi/v1/block/order/create.
    ///
    /// Send in a new block trade order.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#new-block-trade-order
    [[nodiscard]] common::RestApiResponse<NewBlockTradeOrderResponse>
    new_block_trade_order(const NewBlockTradeOrderParams& params) const;

    /// Asynchronous `new_block_trade_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewBlockTradeOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_block_trade_order(const NewBlockTradeOrderParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<NewBlockTradeOrderResponse>(
            client_, new_block_trade_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Block Trade Order (TRADE)
    ///
    /// GET /eapi/v1/block/order/orders.
    ///
    /// Check block trade order status.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-block-trade#query-block-trade-order
    [[nodiscard]] common::RestApiResponse<std::vector<QueryBlockTradeOrderResponseInner>>
    query_block_trade_order(const QueryBlockTradeOrderParams& params = {}) const;

    /// Asynchronous `query_block_trade_order()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryBlockTradeOrderResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_block_trade_order(const QueryBlockTradeOrderParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<QueryBlockTradeOrderResponseInner>>(
            client_, query_block_trade_order_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    accept_block_trade_order_request(const AcceptBlockTradeOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_block_trade_details_request(const QueryBlockTradeDetailsParams& params) const;
    [[nodiscard]] common::RestRequest
    account_block_trade_list_request(const AccountBlockTradeListParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_block_trade_order_request(const CancelBlockTradeOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    extend_block_trade_order_request(const ExtendBlockTradeOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    new_block_trade_order_request(const NewBlockTradeOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_block_trade_order_request(const QueryBlockTradeOrderParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_options::rest_api
