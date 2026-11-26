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

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/cancel_order_response_result.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/modify_order_response_result.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/new_order_response_result.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/position_information_response_result_inner.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/models/query_order_response_result.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

enum class ModifyOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ModifyOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyOrderSideEnum
tag_invoke(boost::json::value_to_tag<ModifyOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, ModifyOrderSideEnum value);

enum class ModifyOrderPriceMatchEnum {
    Opponent,
    Opponent5,
    Opponent10,
    Opponent20,
    Queue,
    Queue5,
    Queue10,
    Queue20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ModifyOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyOrderPriceMatchEnum tag_invoke(
    boost::json::value_to_tag<ModifyOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                ModifyOrderPriceMatchEnum value);

enum class NewOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderSideEnum value);

enum class NewOrderTypeEnum {
    Limit,
    Market,
    Stop,
    StopMarket,
    TakeProfit,
    TakeProfitMarket,
    TrailingStopMarket,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderTypeEnum value);

enum class NewOrderPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderPositionSideEnum tag_invoke(
    boost::json::value_to_tag<NewOrderPositionSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderPositionSideEnum value);

enum class NewOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderTimeInForceEnum value);

enum class NewOrderReduceOnlyEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderReduceOnlyEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderReduceOnlyEnum
tag_invoke(boost::json::value_to_tag<NewOrderReduceOnlyEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderReduceOnlyEnum value);

enum class NewOrderClosePositionEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderClosePositionEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderClosePositionEnum tag_invoke(
    boost::json::value_to_tag<NewOrderClosePositionEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderClosePositionEnum value);

enum class NewOrderWorkingTypeEnum {
    MarkPrice,
    ContractPrice,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderWorkingTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderWorkingTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderWorkingTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderWorkingTypeEnum value);

enum class NewOrderPriceProtectEnum {
    True_,
    False_,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderPriceProtectEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderPriceProtectEnum tag_invoke(
    boost::json::value_to_tag<NewOrderPriceProtectEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderPriceProtectEnum value);

enum class NewOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderNewOrderRespTypeEnum value);

enum class NewOrderPriceMatchEnum {
    Opponent,
    Opponent5,
    Opponent10,
    Opponent20,
    Queue,
    Queue5,
    Queue10,
    Queue20,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderPriceMatchEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderPriceMatchEnum
tag_invoke(boost::json::value_to_tag<NewOrderPriceMatchEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                NewOrderPriceMatchEnum value);

enum class NewOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireBoth,
    ExpireMaker,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(NewOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewOrderSelfTradePreventionModeEnum value);

struct CancelOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyOrderParams {
    common::Required<std::string> symbol;
    common::Required<ModifyOrderSideEnum> side;
    /// Order quantity, cannot be sent with `closePosition=true`
    common::Required<common::Decimal> quantity;
    common::Required<common::Decimal> price;
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<ModifyOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewOrderParams {
    common::Required<std::string> symbol;
    common::Required<NewOrderSideEnum> side;
    /// **After CM migration, stop-type values (`STOP`, `STOP_MARKET`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_MARKET`, `TRAILING_STOP_MARKET`) are no longer accepted and will return
    /// `-4120`. Use the REST `/dapi/v1/algoOrder` endpoint instead.**
    common::Required<NewOrderTypeEnum> type;
    std::optional<std::string> id = std::nullopt;
    /// Default `BOTH` for One-way Mode; `LONG` or `SHORT` for Hedge Mode.  It must be sent in Hedge
    /// Mode.
    std::optional<NewOrderPositionSideEnum> position_side = std::nullopt;
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// Quantity measured by contract number, Cannot be sent with `closePosition`=`true`
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Cannot be sent in Hedge Mode; cannot be sent with `closePosition`=`true` (Close-All)"
    std::optional<NewOrderReduceOnlyEnum> reduce_only = std::nullopt;
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// `true`, `false`；Close-All，used with `STOP_MARKET` or `TAKE_PROFIT_MARKET`.
    std::optional<NewOrderClosePositionEnum> close_position = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, default as the latest price(supporting different
    /// workingType)
    std::optional<common::Decimal> activation_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, min 0.1, max 10 where 1 for 1%
    std::optional<common::Decimal> callback_rate = std::nullopt;
    /// stopPrice triggered by: "MARK_PRICE", "CONTRACT_PRICE". Default "CONTRACT_PRICE"
    std::optional<NewOrderWorkingTypeEnum> working_type = std::nullopt;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.'
    std::optional<NewOrderPriceProtectEnum> price_protect = std::nullopt;
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only available for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<NewOrderPriceMatchEnum> price_match = std::nullopt;
    /// `NONE`: No STP / `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`:
    /// expire taker order when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationParams {
    std::optional<std::string> id = std::nullopt;
    std::optional<std::string> margin_asset = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOrderParams {
    common::Required<std::string> symbol;
    std::optional<std::string> id = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::WebsocketApi> client);

    /// Cancel Order (TRADE)
    ///
    /// `order.cancel`.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/trade#cancel-order
    [[nodiscard]] common::WebsocketApiResponse<CancelOrderResponseResult>
    cancel_order(const CancelOrderParams& params) const;

    /// Asynchronous `cancel_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<CancelOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelOrderResponseResult>(
            client_, "order.cancel", cancel_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// `order.modify`.
    ///
    /// Order modify function, currently only LIMIT order modification is
    /// supported, modified orders will be reordered in the match queue
    ///
    /// Weight: 1 on 10s order rate limit(X-MBX-ORDER-COUNT-10S);
    /// 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M);
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Both `quantity` and `price` must be sent.
    /// - When the new `quantity` or `price` doesn't satisfy `PRICE_FILTER` / `PERCENT_FILTER` /
    /// `LOT_SIZE`, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    /// - One order can only be modified for less than 10000 times.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/trade#modify-order
    [[nodiscard]] common::WebsocketApiResponse<ModifyOrderResponseResult>
    modify_order(const ModifyOrderParams& params) const;

    /// Asynchronous `modify_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<ModifyOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyOrderResponseResult>(
            client_, "order.modify", modify_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// `order.place`.
    ///
    /// Send in a new order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on `type`:
    ///   | Type | Additional mandatory parameters |  | :---: | --- |  | `LIMIT` | `timeInForce`,
    ///   `quantity`, `price` | | `MARKET` | `quantity` | | `STOP/TAKE_PROFIT` | `quantity`,
    ///   `price`, `stopPrice` | | `STOP_MARKET/TAKE_PROFIT_MARKET` | `stopPrice` | |
    ///   `TRAILING_STOP_MARKET` | `callbackRate` |
    ///   - Order with type `STOP`, parameter `timeInForce` can be sent ( default `GTC`). * Order
    ///   with type `TAKE_PROFIT`, parameter `timeInForce` can be sent ( default `GTC`). * Condition
    ///   orders will be triggered when:
    ///   - If parameter `priceProtect` is sent as true:
    ///   - when price reaches the `stopPrice`，the difference rate between "MARK_PRICE" and
    ///   "CONTRACT_PRICE" cannot be larger than the "triggerProtect" of the symbol
    ///   - "triggerProtect" of a symbol can be got from `GET /dapi/v1/exchangeInfo`
    ///   - `STOP`, `STOP_MARKET`:
    ///   - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///   - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///   - `TAKE_PROFIT`, `TAKE_PROFIT_MARKET`:
    ///   - BUY: latest price ("MARK_PRICE" or "CONTRACT_PRICE") <= `stopPrice`
    ///   - SELL: latest price ("MARK_PRICE" or "CONTRACT_PRICE") >= `stopPrice`
    ///   - `TRAILING_STOP_MARKET`:
    ///   - BUY: the lowest price after order placed <= `activationPrice`, and the latest price >=
    ///   the lowest price * (1 + `callbackRate`)
    ///   - SELL: the highest price after order placed >= `activationPrice`, and the latest price <=
    ///   the highest price * (1 - `callbackRate`)
    ///   - For `TRAILING_STOP_MARKET`, if you got such error code.
    ///   - BUY: `activationPrice` should be smaller than latest price.
    ///   - SELL: `activationPrice` should be larger than latest price.
    ///   - If `newOrderRespType` is sent as `RESULT`:
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///   - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition=true`:
    ///   - Follow the same rules for condition orders.
    ///   - If triggered，**close all** current long position(if `SELL`) or current short
    ///   position(if `BUY`).
    ///   - Cannot be used with `quantity` parameter
    ///   - Cannot be used with `reduceOnly` parameter
    ///   - In Hedge Mode, cannot be used with `BUY` orders in `LONG` position side. and cannot be
    ///   used with `SELL` orders in `SHORT` position side
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/trade#new-order
    [[nodiscard]] common::WebsocketApiResponse<NewOrderResponseResult>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<NewOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponseResult>(
            client_, "order.place", new_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Position Information (USER_DATA)
    ///
    /// `account.position`.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/trade#position-information
    [[nodiscard]] common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>
    position_information(const PositionInformationParams& params = {}) const;

    /// Asynchronous `position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::WebsocketApiResponse<std::vector<PositionInformationResponseResultInner>>)`.
    template <class CompletionToken>
    auto async_position_information(const PositionInformationParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationResponseResultInner>>(
            client_, "account.position", position_information_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// `order.status`.
    ///
    /// Check an order's status.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `EXPIRED` **AND** order has NO filled trade **AND**
    ///   created time + 3 days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/ws-api/trade#query-order
    [[nodiscard]] common::WebsocketApiResponse<QueryOrderResponseResult>
    query_order(const QueryOrderParams& params) const;

    /// Asynchronous `query_order()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<QueryOrderResponseResult>)`.
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryOrderResponseResult>(
            client_, "order.status", query_order_payload(params),
            make_options(false, true, false, false), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params cancel_order_payload(const CancelOrderParams& params);
    [[nodiscard]] static common::Params modify_order_payload(const ModifyOrderParams& params);
    [[nodiscard]] static common::Params new_order_payload(const NewOrderParams& params);
    [[nodiscard]] static common::Params
    position_information_payload(const PositionInformationParams& params);
    [[nodiscard]] static common::Params query_order_payload(const QueryOrderParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::derivatives_trading_coin_futures::websocket_api
