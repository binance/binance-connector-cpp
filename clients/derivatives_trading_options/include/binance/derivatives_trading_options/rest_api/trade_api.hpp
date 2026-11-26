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
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_all_option_orders_by_underlying_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_all_option_orders_on_specific_symbol_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_multiple_option_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_option_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_position_information_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_current_open_option_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_option_order_history_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_single_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/tradfi_options_contract_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_commission_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_exercise_record_response_inner.hpp>

namespace binance::derivatives_trading_options::rest_api {

enum class NewOrderSideEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewOrderSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewOrderSideEnum
tag_invoke(boost::json::value_to_tag<NewOrderSideEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderSideEnum value);

enum class NewOrderTypeEnum {
    Limit,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewOrderTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewOrderTypeEnum
tag_invoke(boost::json::value_to_tag<NewOrderTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, NewOrderTypeEnum value);

enum class NewOrderTimeInForceEnum {
    Gtc,
    Ioc,
    Fok,
    Gtx,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewOrderTimeInForceEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewOrderTimeInForceEnum tag_invoke(
    boost::json::value_to_tag<NewOrderTimeInForceEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           NewOrderTimeInForceEnum value);

enum class NewOrderNewOrderRespTypeEnum {
    Ack,
    Result,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewOrderNewOrderRespTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewOrderNewOrderRespTypeEnum tag_invoke(
    boost::json::value_to_tag<NewOrderNewOrderRespTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                           boost::json::value& jv,
                                                           NewOrderNewOrderRespTypeEnum value);

enum class NewOrderSelfTradePreventionModeEnum {
    None_,
    ExpireTaker,
    ExpireMaker,
    ExpireBoth,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT std::string_view
to_string(NewOrderSelfTradePreventionModeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT NewOrderSelfTradePreventionModeEnum
tag_invoke(boost::json::value_to_tag<NewOrderSelfTradePreventionModeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           NewOrderSelfTradePreventionModeEnum value);

struct AccountTradeListParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Trade id to fetch from. Default gets most recent trades, e.g 4611875134427365376
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllOptionOrdersByUnderlyingParams {
    /// Underlying asset.
    common::Required<std::string> underlying;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllOptionOrdersOnSpecificSymbolParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMultipleOptionOrdersParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Order ID list.
    std::optional<std::vector<std::int64_t>> order_ids = std::nullopt;
    /// Client order ID list.
    std::optional<std::vector<std::string>> client_order_ids = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PlaceMultipleOrdersParams {
    /// order list. Max 10 orders
    common::Required<std::vector<PlaceMultipleOrdersOrdersParameterInner>> orders;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelOptionOrderParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Order ID.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// clientOrderId
    std::optional<std::string> client_order_id = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewOrderParams {
    common::Required<std::string> symbol;
    common::Required<NewOrderSideEnum> side;
    common::Required<NewOrderTypeEnum> type;
    /// Order Quantity
    common::Required<common::Decimal> quantity;
    /// Order Price
    std::optional<common::Decimal> price = std::nullopt;
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    std::optional<bool> reduce_only = std::nullopt;
    std::optional<bool> post_only = std::nullopt;
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// User-defined order ID cannot be repeated in pending orders
    std::optional<std::string> client_order_id = std::nullopt;
    /// is market maker protection order
    std::optional<bool> is_mmp = std::nullopt;
    /// Self-trade prevention mode
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QuerySingleOrderParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Order ID.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// User-defined order ID; cannot be duplicated among open orders.
    std::optional<std::string> client_order_id = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct OptionPositionInformationParams {
    /// Option trading pair.
    std::optional<std::string> symbol = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentOpenOptionOrdersParams {
    /// Option trading pair.
    std::optional<std::string> symbol = std::nullopt;
    /// Order ID.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOptionOrderHistoryParams {
    /// Option trading pair.
    common::Required<std::string> symbol;
    /// Order ID.
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned
    std::optional<std::int64_t> limit = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct TradfiOptionsContractParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserCommissionParams {
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UserExerciseRecordParams {
    /// Option trading pair.
    std::optional<std::string> symbol = std::nullopt;
    /// Start Time, e.g 1593511200000
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End Time, e.g 1593512200000
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of result sets returned.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Account Trade List (USER_DATA)
    ///
    /// GET /eapi/v1/userTrades.
    ///
    /// Get trades for a specific account and symbol. Only supports querying trades in the past 3
    /// months; a `startTime`/`endTime` outside that window returns `-6073
    /// SEARCH_WINDOW_RESTRICTED`.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
    account_trade_list(const AccountTradeListParams& params) const;

    /// Asynchronous `account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_account_trade_list(const AccountTradeListParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<AccountTradeListResponseInner>>(
            client_, account_trade_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel All Option Orders By Underlying (TRADE)
    ///
    /// DELETE /eapi/v1/allOpenOrdersByUnderlying.
    ///
    /// Cancel all active orders on specified underlying.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-all-option-orders-by-underlying
    [[nodiscard]] common::RestApiResponse<CancelAllOptionOrdersByUnderlyingResponse>
    cancel_all_option_orders_by_underlying(
        const CancelAllOptionOrdersByUnderlyingParams& params) const;

    /// Asynchronous `cancel_all_option_orders_by_underlying()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<CancelAllOptionOrdersByUnderlyingResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders_by_underlying(
        const CancelAllOptionOrdersByUnderlyingParams& params, CompletionToken&& token) const {
        return common::async_send<CancelAllOptionOrdersByUnderlyingResponse>(
            client_, cancel_all_option_orders_by_underlying_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel all Option orders on specific symbol (TRADE)
    ///
    /// DELETE /eapi/v1/allOpenOrders.
    ///
    /// Cancel all active order on a symbol.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-all-option-orders-on-specific-symbol
    [[nodiscard]] common::RestApiResponse<CancelAllOptionOrdersOnSpecificSymbolResponse>
    cancel_all_option_orders_on_specific_symbol(
        const CancelAllOptionOrdersOnSpecificSymbolParams& params) const;

    /// Asynchronous `cancel_all_option_orders_on_specific_symbol()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<CancelAllOptionOrdersOnSpecificSymbolResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_option_orders_on_specific_symbol(
        const CancelAllOptionOrdersOnSpecificSymbolParams& params, CompletionToken&& token) const {
        return common::async_send<CancelAllOptionOrdersOnSpecificSymbolResponse>(
            client_, cancel_all_option_orders_on_specific_symbol_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel Multiple Option Orders (TRADE)
    ///
    /// DELETE /eapi/v1/batchOrders.
    ///
    /// Cancel multiple orders.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - At least one instance of `orderId` and `clientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-multiple-option-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CancelMultipleOptionOrdersResponseInner>>
    cancel_multiple_option_orders(const CancelMultipleOptionOrdersParams& params) const;

    /// Asynchronous `cancel_multiple_option_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CancelMultipleOptionOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_cancel_multiple_option_orders(const CancelMultipleOptionOrdersParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<CancelMultipleOptionOrdersResponseInner>>(
            client_, cancel_multiple_option_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Place Multiple Orders (TRADE)
    ///
    /// POST /eapi/v1/batchOrders.
    ///
    /// Send multiple option orders.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Some parameters are mandatory depending on the order type as follows:
    ///
    /// Type | Mandatory parameters
    /// ------------ | ------------
    /// LIMIT | timeInForce, quantity, price
    ///
    /// - Parameter rules are same with New Order
    /// - Batch orders are processed concurrently, and the order of matching is not guaranteed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#place-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>
    place_multiple_orders(const PlaceMultipleOrdersParams& params) const;

    /// Asynchronous `place_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PlaceMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_place_multiple_orders(const PlaceMultipleOrdersParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<PlaceMultipleOrdersResponseInner>>(
            client_, place_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel Option Order (TRADE)
    ///
    /// DELETE /eapi/v1/order.
    ///
    /// Cancel an active order.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - At least one instance of `orderId` and `clientOrderId` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#cancel-option-order
    [[nodiscard]] common::RestApiResponse<CancelOptionOrderResponse>
    cancel_option_order(const CancelOptionOrderParams& params) const;

    /// Asynchronous `cancel_option_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelOptionOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_option_order(const CancelOptionOrderParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<CancelOptionOrderResponse>(
            client_, cancel_option_order_request(params), std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// POST /eapi/v1/order.
    ///
    /// Send a new order.
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// Some parameters are mandatory depending on the order type as follows:
    ///
    /// Type | Mandatory parameters
    /// ------------ | ------------
    /// LIMIT | timeInForce, quantity, price
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponse>(client_, new_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Query Single Order (TRADE)
    ///
    /// GET /eapi/v1/order.
    ///
    /// Check an order status.
    ///
    /// * These orders will not be found:
    ///   * order status is `CANCELED` or `REJECTED`, **AND**
    ///   * order has NO filled trade, **AND**
    ///   * created time + 3 days < current time
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `clientOrderId ` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-single-order
    [[nodiscard]] common::RestApiResponse<QuerySingleOrderResponse>
    query_single_order(const QuerySingleOrderParams& params) const;

    /// Asynchronous `query_single_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QuerySingleOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_single_order(const QuerySingleOrderParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<QuerySingleOrderResponse>(
            client_, query_single_order_request(params), std::forward<CompletionToken>(token));
    }

    /// Option Position Information (USER_DATA)
    ///
    /// GET /eapi/v1/position.
    ///
    /// Get current position information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#option-position-information
    [[nodiscard]] common::RestApiResponse<std::vector<OptionPositionInformationResponseInner>>
    option_position_information(const OptionPositionInformationParams& params = {}) const;

    /// Asynchronous `option_position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OptionPositionInformationResponseInner>>)`.
    template <class CompletionToken>
    auto async_option_position_information(const OptionPositionInformationParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<std::vector<OptionPositionInformationResponseInner>>(
            client_, option_position_information_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Current Open Option Orders (USER_DATA)
    ///
    /// GET /eapi/v1/openOrders.
    ///
    /// Query current all open orders, status: ACCEPTED PARTIALLY_FILLED
    ///
    /// Weight: 1 for a single symbol; 40 when the symbol parameter is omitted
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-current-open-option-orders
    [[nodiscard]] common::RestApiResponse<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>
    query_current_open_option_orders(const QueryCurrentOpenOptionOrdersParams& params = {}) const;

    /// Asynchronous `query_current_open_option_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_current_open_option_orders(const QueryCurrentOpenOptionOrdersParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<QueryCurrentOpenOptionOrdersResponseInner>>(
            client_, query_current_open_option_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Option Order History (TRADE)
    ///
    /// GET /eapi/v1/historyOrders.
    ///
    /// Query all finished orders within 5 days, finished status: CANCELLED FILLED REJECTED.
    ///
    /// Weight(IP): 3
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#query-option-order-history
    [[nodiscard]] common::RestApiResponse<std::vector<QueryOptionOrderHistoryResponseInner>>
    query_option_order_history(const QueryOptionOrderHistoryParams& params) const;

    /// Asynchronous `query_option_order_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QueryOptionOrderHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_query_option_order_history(const QueryOptionOrderHistoryParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<QueryOptionOrderHistoryResponseInner>>(
            client_, query_option_order_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// TradFi Options Contract (USER_DATA)
    ///
    /// POST /eapi/v1/stock/contract.
    ///
    /// Sign TradFi Options agreement contract
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#tradfi-options-contract
    [[nodiscard]] common::RestApiResponse<TradfiOptionsContractResponse>
    tradfi_options_contract(const TradfiOptionsContractParams& params = {}) const;

    /// Asynchronous `tradfi_options_contract()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TradfiOptionsContractResponse>)`.
    template <class CompletionToken>
    auto async_tradfi_options_contract(const TradfiOptionsContractParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<TradfiOptionsContractResponse>(
            client_, tradfi_options_contract_request(params), std::forward<CompletionToken>(token));
    }

    /// User Commission (USER_DATA)
    ///
    /// GET /eapi/v1/commission.
    ///
    /// Get account commission.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#user-commission
    [[nodiscard]] common::RestApiResponse<UserCommissionResponse>
    user_commission(const UserCommissionParams& params = {}) const;

    /// Asynchronous `user_commission()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<UserCommissionResponse>)`.
    template <class CompletionToken>
    auto async_user_commission(const UserCommissionParams& params, CompletionToken&& token) const {
        return common::async_send<UserCommissionResponse>(client_, user_commission_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// User Exercise Record (USER_DATA)
    ///
    /// GET /eapi/v1/exerciseRecord.
    ///
    /// Get account exercise records.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/trade#user-exercise-record
    [[nodiscard]] common::RestApiResponse<std::vector<UserExerciseRecordResponseInner>>
    user_exercise_record(const UserExerciseRecordParams& params = {}) const;

    /// Asynchronous `user_exercise_record()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UserExerciseRecordResponseInner>>)`.
    template <class CompletionToken>
    auto async_user_exercise_record(const UserExerciseRecordParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<UserExerciseRecordResponseInner>>(
            client_, user_exercise_record_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_trade_list_request(const AccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest cancel_all_option_orders_by_underlying_request(
        const CancelAllOptionOrdersByUnderlyingParams& params) const;
    [[nodiscard]] common::RestRequest cancel_all_option_orders_on_specific_symbol_request(
        const CancelAllOptionOrdersOnSpecificSymbolParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_multiple_option_orders_request(const CancelMultipleOptionOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_option_order_request(const CancelOptionOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_order_request(const NewOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    query_single_order_request(const QuerySingleOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    option_position_information_request(const OptionPositionInformationParams& params) const;
    [[nodiscard]] common::RestRequest query_current_open_option_orders_request(
        const QueryCurrentOpenOptionOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    query_option_order_history_request(const QueryOptionOrderHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    tradfi_options_contract_request(const TradfiOptionsContractParams& params) const;
    [[nodiscard]] common::RestRequest
    user_commission_request(const UserCommissionParams& params) const;
    [[nodiscard]] common::RestRequest
    user_exercise_record_request(const UserExerciseRecordParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_options::rest_api
