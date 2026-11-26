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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/all_orders_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/cancel_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/cancel_order_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/change_initial_leverage_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/change_margin_type_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/change_position_mode_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/current_all_open_orders_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_order_modify_history_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_position_margin_change_history_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_isolated_position_margin_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_multiple_orders_batch_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/modify_order_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/new_order_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/place_multiple_orders_batch_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/place_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/position_adl_quantile_estimation_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/position_information_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/query_current_open_order_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/query_order_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/users_force_orders_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

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

enum class ChangeMarginTypeMarginTypeEnum {
    Isolated,
    Crossed,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ChangeMarginTypeMarginTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ChangeMarginTypeMarginTypeEnum
tag_invoke(boost::json::value_to_tag<ChangeMarginTypeMarginTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ChangeMarginTypeMarginTypeEnum value);

enum class ModifyIsolatedPositionMarginPositionSideEnum {
    Both,
    Long,
    Short,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ModifyIsolatedPositionMarginPositionSideEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ModifyIsolatedPositionMarginPositionSideEnum
tag_invoke(boost::json::value_to_tag<ModifyIsolatedPositionMarginPositionSideEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ModifyIsolatedPositionMarginPositionSideEnum value);

enum class UsersForceOrdersAutoCloseTypeEnum {
    Liquidation,
    Adl,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(UsersForceOrdersAutoCloseTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT UsersForceOrdersAutoCloseTypeEnum
tag_invoke(boost::json::value_to_tag<UsersForceOrdersAutoCloseTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           UsersForceOrdersAutoCloseTypeEnum value);

struct AccountTradeListParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// pair
    std::optional<std::string> pair = std::nullopt;
    /// Order ID
    std::optional<std::string> order_id = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Trade id to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AllOrdersParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Pair
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct AutoCancelAllOpenOrdersParams {
    common::Required<std::string> symbol;
    /// countdown time, 1000 for 1 second. 0 to cancel the timer
    common::Required<std::int64_t> countdown_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelAllOpenOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelMultipleOrdersParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order IDs to cancel.
    std::optional<std::vector<std::int64_t>> order_id_list = std::nullopt;
    /// Original client order IDs to cancel.
    std::optional<std::vector<std::string>> orig_client_order_id_list = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyMultipleOrdersParams {
    /// order list. Max 5 orders
    common::Required<std::vector<ModifyMultipleOrdersBatchOrdersParameterInner>> batch_orders;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PlaceMultipleOrdersParams {
    /// order list. Max 5 orders
    common::Required<std::vector<PlaceMultipleOrdersBatchOrdersParameterInner>> batch_orders;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CancelOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<ModifyOrderSideEnum> side;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Order quantity, cannot be sent with `closePosition=true`. **After CM migration, this
    /// parameter becomes mandatory** (must be sent together with `price`).
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Order price. **After CM migration, this parameter becomes mandatory** (must be sent together
    /// with `quantity`).
    std::optional<common::Decimal> price = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<ModifyOrderPriceMatchEnum> price_match = std::nullopt;
    /// User-defined modification identifier, returned as-is in the response. Optional; not
    /// validated for uniqueness.
    std::optional<std::int64_t> modify_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct NewOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<NewOrderSideEnum> side;
    /// **After CM migration, stop-type values (`STOP`, `STOP_MARKET`, `TAKE_PROFIT`,
    /// `TAKE_PROFIT_MARKET`, `TRAILING_STOP_MARKET`) are no longer accepted by this endpoint and
    /// will return `-4120`. Use the new `/dapi/v1/algoOrder` endpoint instead.**
    common::Required<NewOrderTypeEnum> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent in Hedge
    /// Mode.
    std::optional<NewOrderPositionSideEnum> position_side = std::nullopt;
    /// "true" or "false". Cannot be sent in Hedge Mode; cannot be sent with
    /// `closePosition`=`true`(Close-All)
    std::optional<NewOrderReduceOnlyEnum> reduce_only = std::nullopt;
    /// quantity measured by contract number, Cannot be sent with `closePosition`=`true`
    std::optional<common::Decimal> quantity = std::nullopt;
    /// Order price
    std::optional<common::Decimal> price = std::nullopt;
    /// A unique id among open orders. Automatically generated if not sent. Can only be string
    /// following the rule: `^[\.A-Z\:/a-z0-9_-]{1,36}$`
    std::optional<std::string> new_client_order_id = std::nullopt;
    /// Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<common::Decimal> stop_price = std::nullopt;
    /// `true`, `false`；Close-All,used with `STOP_MARKET` or `TAKE_PROFIT_MARKET`.
    std::optional<std::string> close_position = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, default as the latest price(supporting different
    /// `workingType`)
    std::optional<common::Decimal> activation_price = std::nullopt;
    /// Used with `TRAILING_STOP_MARKET` orders, min 0.1, max 10 where 1 for 1%
    std::optional<common::Decimal> callback_rate = std::nullopt;
    std::optional<NewOrderTimeInForceEnum> time_in_force = std::nullopt;
    /// 'stopPrice triggered by: "MARK_PRICE", "CONTRACT_PRICE".
    std::optional<NewOrderWorkingTypeEnum> working_type = std::nullopt;
    /// "true" or "false". Used with `STOP/STOP_MARKET` or `TAKE_PROFIT/TAKE_PROFIT_MARKET` orders.
    std::optional<NewOrderPriceProtectEnum> price_protect = std::nullopt;
    std::optional<NewOrderNewOrderRespTypeEnum> new_order_resp_type = std::nullopt;
    /// only avaliable for `LIMIT`/`STOP`/`TAKE_PROFIT` order; Can't be passed together with `price`
    std::optional<NewOrderPriceMatchEnum> price_match = std::nullopt;
    /// `EXPIRE_TAKER`: expire taker order when STP triggers/ `EXPIRE_MAKER`: expire taker order
    /// when STP triggers/ `EXPIRE_BOTH`: expire both orders when STP triggers
    std::optional<NewOrderSelfTradePreventionModeEnum> self_trade_prevention_mode = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeInitialLeverageParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// target initial leverage: int from 1 to 125
    common::Required<std::int64_t> leverage;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangeMarginTypeParams {
    /// Symbol
    common::Required<std::string> symbol;
    common::Required<ChangeMarginTypeMarginTypeEnum> margin_type;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ChangePositionModeParams {
    /// "true": Hedge Mode; "false": One-way Mode
    common::Required<std::string> dual_side_position;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct CurrentAllOpenOrdersParams {
    /// Symbol. **After CM migration, an invalid `symbol` returns `-1121` (previously a silent
    /// `200`).**
    std::optional<std::string> symbol = std::nullopt;
    /// Pair
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetOrderModifyHistoryParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    /// Timestamp in ms to get modification history from INCLUSIVE
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get modification history until INCLUSIVE
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetPositionMarginChangeHistoryParams {
    common::Required<std::string> symbol;
    /// 1: Add position margin,2: Reduce position margin
    std::optional<std::int64_t> type = std::nullopt;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ModifyIsolatedPositionMarginParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Margin asset
    common::Required<common::Decimal> amount;
    /// 1: Add position margin,2: Reduce position margin
    common::Required<std::int64_t> type;
    /// Default `BOTH` for One-way Mode ; `LONG` or `SHORT` for Hedge Mode. It must be sent with
    /// Hedge Mode.
    std::optional<ModifyIsolatedPositionMarginPositionSideEnum> position_side = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionAdlQuantileEstimationParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct PositionInformationParams {
    std::optional<std::string> margin_asset = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryCurrentOpenOrderParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Order ID
    std::optional<std::int64_t> order_id = std::nullopt;
    /// Client order ID
    std::optional<std::string> orig_client_order_id = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct UsersForceOrdersParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<UsersForceOrdersAutoCloseTypeEnum> auto_close_type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Account Trade List (USER_DATA)
    ///
    /// GET /dapi/v1/userTrades.
    ///
    /// Get trades for a specific account and symbol.
    ///
    /// Weight: **20** with symbol，**40** with pair (after CM migration: **5** flat)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either symbol or pair must be sent
    /// - Symbol and pair cannot be sent together
    /// - Pair and fromId cannot be sent together
    /// - OrderId can only be sent together with symbol
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - The parameter `fromId` cannot be sent with `startTime` or `endTime`
    /// - If startTime and endTime are both not sent, then the last 7 days' data will be returned.
    /// - The time between startTime and endTime cannot be longer than 7 days.
    /// - Only support querying trade in the past 3 months
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#account-trade-list
    [[nodiscard]] common::RestApiResponse<std::vector<AccountTradeListResponseInner>>
    account_trade_list(const AccountTradeListParams& params = {}) const;

    /// Asynchronous `account_trade_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<AccountTradeListResponseInner>>)`.
    template <class CompletionToken>
    auto async_account_trade_list(const AccountTradeListParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<AccountTradeListResponseInner>>(
            client_, account_trade_list_request(params), std::forward<CompletionToken>(token));
    }

    /// All Orders (USER_DATA)
    ///
    /// GET /dapi/v1/allOrders.
    ///
    /// Get all account orders; active, canceled, or filled.
    ///
    /// * These orders will not be found:
    ///   * order status is CANCELED or EXPIRED AND order has NO filled trade AND created time + 3
    ///   days < current time
    ///   * order create time + 90 days < current time
    ///
    /// Weight: **20** with symbol, **40** with pair (after CM migration: **5** flat)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `symbol` or `pair` must be sent.
    /// - `pair` can't be sent with `orderId`
    /// - If `orderId` is set, it will get orders >= that `orderId`. Otherwise most recent orders
    /// are returned.
    /// - If orderId is set, it will get orders >= that orderId. Otherwise most recent orders are
    /// returned.
    /// - The query time period must be less then 7 days( default as the recent 7 days).
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#all-orders
    [[nodiscard]] common::RestApiResponse<std::vector<AllOrdersResponseInner>>
    all_orders(const AllOrdersParams& params = {}) const;

    /// Asynchronous `all_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<AllOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_all_orders(const AllOrdersParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<AllOrdersResponseInner>>(
            client_, all_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Auto-Cancel All Open Orders (TRADE)
    ///
    /// POST /dapi/v1/countdownCancelAll.
    ///
    /// Cancel all open orders of the specified symbol at the end of the
    /// specified countdown. This rest endpoint means to ensure your open orders
    /// are canceled in case of an outage. The endpoint should be called
    /// repeatedly as heartbeats so that the existing countdown time can be
    /// canceled and repalced by a new one. The system will check all countdowns
    /// **approximately every 10 milliseconds**, so please note that sufficient
    /// redundancy should be considered when using this function. We do not
    /// recommend setting the countdown time to be too precise or too small.
    ///
    /// * Example usage:
    ///
    /// Call this endpoint at 30s intervals with an countdownTime of 120000
    /// (120s).
    ///
    /// If this endpoint is not called within 120 seconds, all your orders of
    /// the specified symbol will be automatically canceled.
    ///
    /// If this endpoint is called with an countdownTime of 0, the countdown
    /// timer will be stopped.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
    auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const;

    /// Asynchronous `auto_cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AutoCancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<AutoCancelAllOpenOrdersResponse>(
            client_, auto_cancel_all_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Cancel All Open Orders (TRADE)
    ///
    /// DELETE /dapi/v1/allOpenOrders.
    ///
    /// Cancel All Open Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<CancelAllOpenOrdersResponse>
    cancel_all_open_orders(const CancelAllOpenOrdersParams& params) const;

    /// Asynchronous `cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_cancel_all_open_orders(const CancelAllOpenOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<CancelAllOpenOrdersResponse>(
            client_, cancel_all_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Cancel Multiple Orders (TRADE)
    ///
    /// DELETE /dapi/v1/batchOrders.
    ///
    /// Cancel Multiple Orders
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderIdList` or `origClientOrderIdList ` must be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>
    cancel_multiple_orders(const CancelMultipleOrdersParams& params) const;

    /// Asynchronous `cancel_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CancelMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_cancel_multiple_orders(const CancelMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<CancelMultipleOrdersResponseInner>>(
            client_, cancel_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Modify Multiple Orders (TRADE)
    ///
    /// PUT /dapi/v1/batchOrders.
    ///
    /// Modify Multiple Orders
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Parameter rules are same with `Modify Order`
    /// - Batch modify orders are processed concurrently, and the order of matching is not
    /// guaranteed.
    /// - The order of returned contents for batch modify orders is the same as the order of the
    /// order list.
    /// - One order can only be modfied for less than 10000 times
    /// - `modifyId` is an optional user-defined identifier passed through as-is; the server does
    /// not validate its uniqueness. If omitted, it is not included in the response.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-multiple-orders
    [[nodiscard]] common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>
    modify_multiple_orders(const ModifyMultipleOrdersParams& params) const;

    /// Asynchronous `modify_multiple_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<ModifyMultipleOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_modify_multiple_orders(const ModifyMultipleOrdersParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<ModifyMultipleOrdersResponseInner>>(
            client_, modify_multiple_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Place Multiple Orders (TRADE)
    ///
    /// POST /dapi/v1/batchOrders.
    ///
    /// Place multiple orders
    ///
    /// * Parameter rules are same with `New Order`
    /// * Batch orders are processed concurrently, and the order of matching is not guaranteed.
    /// * The order of returned contents for batch orders is the same as the order of the order
    /// list.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `batchOrders` must be a JSON array of order parameter objects.
    /// - Example:
    ///   `/dapi/v1/batchOrders?batchOrders=[{"type":"LIMIT","timeInForce":"GTC","symbol":"BTCUSD_PERP","side":"BUY","price":"10001","quantity":"1"}]`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#place-multiple-orders
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

    /// Cancel Order (TRADE)
    ///
    /// DELETE /dapi/v1/order.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#cancel-order
    [[nodiscard]] common::RestApiResponse<CancelOrderResponse>
    cancel_order(const CancelOrderParams& params) const;

    /// Asynchronous `cancel_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CancelOrderResponse>)`.
    template <class CompletionToken>
    auto async_cancel_order(const CancelOrderParams& params, CompletionToken&& token) const {
        return common::async_send<CancelOrderResponse>(client_, cancel_order_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Modify Order (TRADE)
    ///
    /// PUT /dapi/v1/order.
    ///
    /// Order modify function, currently only LIMIT order modification is supported, modified orders
    /// will be reordered in the match queue
    ///
    /// Weight(IP): 0
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Either `quantity` or `price` must be sent. *(After CM migration, both `quantity` and
    /// `price` are required.)*
    /// - When the new `quantity` or `price` doesn't satisfy PRICE_FILTER / PERCENT_FILTER /
    /// LOT_SIZE, amendment will be rejected and the order will stay as it is.
    /// - However the order will be cancelled by the amendment in the following situations:
    ///   - when the order is in partially filled status and the new `quantity` <= `executedQty`
    ///   - When the order is `GTX` and the new price will cause it to be executed immediately
    /// - One order can only be modfied for less than 10000 times
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-order
    [[nodiscard]] common::RestApiResponse<ModifyOrderResponse>
    modify_order(const ModifyOrderParams& params) const;

    /// Asynchronous `modify_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyOrderResponse>)`.
    template <class CompletionToken>
    auto async_modify_order(const ModifyOrderParams& params, CompletionToken&& token) const {
        return common::async_send<ModifyOrderResponse>(client_, modify_order_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// New Order (TRADE)
    ///
    /// POST /dapi/v1/order.
    ///
    /// Send in a new order.
    ///
    /// Weight: 1 on 1min order rate limit(X-MBX-ORDER-COUNT-1M)
    /// 0 on IP rate limit(x-mbx-used-weight-1m)
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Additional mandatory parameters based on `type`:
    ///   - Order with type `STOP`, parameter `timeInForce` can be sent ( default `GTC`).
    ///   - Order with type `TAKE_PROFIT`, parameter `timeInForce` can be sent ( default `GTC`).
    ///   - Condition orders will be triggered when:
    ///   - If parameter`priceProtect`is sent as true:
    ///   - when price reaches the `stopPrice` ，the difference rate between "MARK_PRICE" and
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
    ///
    ///   - For `TRAILING_STOP_MARKET`, if you got such error code. > `{"code": -2021, "msg": "Order
    ///   would immediately trigger."}` > means that the parameters you send do not meet the
    ///   following requirements:
    ///   - BUY: `activationPrice` should be smaller than latest price.
    ///   - SELL: `activationPrice` should be larger than latest price.
    ///   - If `newOrderRespType ` is sent as `RESULT` :
    ///   - `MARKET` order: the final FILLED result of the order will be return directly.
    ///   - `LIMIT` order with special `timeInForce`: the final status result of the order(FILLED or
    ///   EXPIRED) will be returned directly.
    ///   - `STOP_MARKET`, `TAKE_PROFIT_MARKET` with `closePosition`=`true`:
    ///   - Follow the same rules for condition orders.
    ///   - If triggered,**close all** current long position( if `SELL`) or current short position(
    ///   if `BUY`).
    ///   - Cannot be used with `quantity` parameter
    ///   - Cannot be used with `reduceOnly` parameter
    ///   - In Hedge Mode,cannot be used with `BUY` orders in `LONG` position side. and cannot be
    ///   used with `SELL` orders in `SHORT` position side
    ///
    ///   - `selfTradePreventionMode` is only effective when `timeInForce` set to `IOC` or `GTC`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#new-order
    [[nodiscard]] common::RestApiResponse<NewOrderResponse>
    new_order(const NewOrderParams& params) const;

    /// Asynchronous `new_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<NewOrderResponse>)`.
    template <class CompletionToken>
    auto async_new_order(const NewOrderParams& params, CompletionToken&& token) const {
        return common::async_send<NewOrderResponse>(client_, new_order_request(params),
                                                    std::forward<CompletionToken>(token));
    }

    /// Query Order (USER_DATA)
    ///
    /// GET /dapi/v1/order.
    ///
    /// Check an order's status.
    ///
    /// * These orders will not be found:
    ///   * order status is CANCELED or EXPIRED AND order has NO filled trade AND created time + 3
    ///   days < current time
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#query-order
    [[nodiscard]] common::RestApiResponse<QueryOrderResponse>
    query_order(const QueryOrderParams& params) const;

    /// Asynchronous `query_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_order(const QueryOrderParams& params, CompletionToken&& token) const {
        return common::async_send<QueryOrderResponse>(client_, query_order_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Change Initial Leverage (TRADE)
    ///
    /// POST /dapi/v1/leverage.
    ///
    /// Change user's initial leverage in the specific symbol market.
    ///
    /// For Hedge Mode, LONG and SHORT positions of one symbol use the same
    /// initial leverage and share a total notional value.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-initial-leverage
    [[nodiscard]] common::RestApiResponse<ChangeInitialLeverageResponse>
    change_initial_leverage(const ChangeInitialLeverageParams& params) const;

    /// Asynchronous `change_initial_leverage()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeInitialLeverageResponse>)`.
    template <class CompletionToken>
    auto async_change_initial_leverage(const ChangeInitialLeverageParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<ChangeInitialLeverageResponse>(
            client_, change_initial_leverage_request(params), std::forward<CompletionToken>(token));
    }

    /// Change Margin Type (TRADE)
    ///
    /// POST /dapi/v1/marginType.
    ///
    /// Change user's margin type in the specific symbol market.For Hedge Mode,
    /// LONG and SHORT positions of one symbol use the same margin type.
    ///
    /// With ISOLATED margin type, margins of the LONG and SHORT positions are
    /// isolated from each other.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-margin-type
    [[nodiscard]] common::RestApiResponse<ChangeMarginTypeResponse>
    change_margin_type(const ChangeMarginTypeParams& params) const;

    /// Asynchronous `change_margin_type()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangeMarginTypeResponse>)`.
    template <class CompletionToken>
    auto async_change_margin_type(const ChangeMarginTypeParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<ChangeMarginTypeResponse>(
            client_, change_margin_type_request(params), std::forward<CompletionToken>(token));
    }

    /// Change Position Mode (TRADE)
    ///
    /// POST /dapi/v1/positionSide/dual.
    ///
    /// Change user's position mode (Hedge Mode or One-way Mode ) on ***EVERY symbol***.
    ///
    /// **After CM migration**, UM and CM share the **same** `dualSidePosition` setting. Calling
    /// this endpoint flips both UM and CM at once. If either side has any open order or open
    /// position, the change is rejected:
    /// - `-4067` (open orders exist)
    /// - `-4068` (open position exists)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#change-position-mode
    [[nodiscard]] common::RestApiResponse<ChangePositionModeResponse>
    change_position_mode(const ChangePositionModeParams& params) const;

    /// Asynchronous `change_position_mode()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ChangePositionModeResponse>)`.
    template <class CompletionToken>
    auto async_change_position_mode(const ChangePositionModeParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<ChangePositionModeResponse>(
            client_, change_position_mode_request(params), std::forward<CompletionToken>(token));
    }

    /// Current All Open Orders (USER_DATA)
    ///
    /// GET /dapi/v1/openOrders.
    ///
    /// Get all open orders on a symbol. **Careful** when accessing this with no symbol.
    ///
    /// Weight(IP): null
    ///
    /// Weight: **1** for a single symbol, **40** for mutltiple symbols
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#current-all-open-orders
    [[nodiscard]] common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>
    current_all_open_orders(const CurrentAllOpenOrdersParams& params = {}) const;

    /// Asynchronous `current_all_open_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CurrentAllOpenOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_current_all_open_orders(const CurrentAllOpenOrdersParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<std::vector<CurrentAllOpenOrdersResponseInner>>(
            client_, current_all_open_orders_request(params), std::forward<CompletionToken>(token));
    }

    /// Get Order Modify History (USER_DATA)
    ///
    /// GET /dapi/v1/orderAmendment.
    ///
    /// Get order modification history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either `orderId` or `origClientOrderId` must be sent, and the `orderId` will prevail if
    /// both are sent.
    /// - Order modify history longer than 3 month is not avaliable
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#get-order-modify-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>
    get_order_modify_history(const GetOrderModifyHistoryParams& params) const;

    /// Asynchronous `get_order_modify_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetOrderModifyHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_order_modify_history(const GetOrderModifyHistoryParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<GetOrderModifyHistoryResponseInner>>(
            client_, get_order_modify_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Position Margin Change History (TRADE)
    ///
    /// GET /dapi/v1/positionMargin/history.
    ///
    /// Get position margin change history
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#get-position-margin-change-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>
    get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params) const;

    /// Asynchronous `get_position_margin_change_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetPositionMarginChangeHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_get_position_margin_change_history(const GetPositionMarginChangeHistoryParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<GetPositionMarginChangeHistoryResponseInner>>(
            client_, get_position_margin_change_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Modify Isolated Position Margin (TRADE)
    ///
    /// POST /dapi/v1/positionMargin.
    ///
    /// Modify Isolated Position Margin
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Only for isolated symbol
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#modify-isolated-position-margin
    [[nodiscard]] common::RestApiResponse<ModifyIsolatedPositionMarginResponse>
    modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params) const;

    /// Asynchronous `modify_isolated_position_margin()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ModifyIsolatedPositionMarginResponse>)`.
    template <class CompletionToken>
    auto async_modify_isolated_position_margin(const ModifyIsolatedPositionMarginParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<ModifyIsolatedPositionMarginResponse>(
            client_, modify_isolated_position_margin_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Position ADL Quantile Estimation (USER_DATA)
    ///
    /// GET /dapi/v1/adlQuantile.
    ///
    /// Query position ADL quantile estimation
    ///
    /// * Values update every 30s.
    /// * Values 0, 1, 2, 3, 4 shows the queue position and possibility of ADL from low to high.
    /// * For positions of the symbol are in One-way Mode or isolated margined in Hedge Mode,
    /// "LONG", "SHORT", and "BOTH" will be returned to show the positions' adl quantiles of
    /// different position sides.
    /// * If the positions of the symbol are crossed margined in Hedge Mode:
    ///   * "HEDGE" as a sign will be returned instead of "BOTH";
    ///   * A same value caculated on unrealized pnls on long and short sides' positions will be
    ///   shown for "LONG" and "SHORT" when there are positions in both of long and short sides.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#position-adl-quantile-estimation
    [[nodiscard]] common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>
    position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params = {}) const;

    /// Asynchronous `position_adl_quantile_estimation()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PositionAdlQuantileEstimationResponseInner>>)`.
    template <class CompletionToken>
    auto async_position_adl_quantile_estimation(const PositionAdlQuantileEstimationParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<PositionAdlQuantileEstimationResponseInner>>(
            client_, position_adl_quantile_estimation_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Position Information (USER_DATA)
    ///
    /// GET /dapi/v1/positionRisk.
    ///
    /// Get current account information.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If neither `marginAsset` nor `pair` is sent, positions of all symbols with `TRADING`
    /// status will be returned.
    /// - for One-way Mode user, the response will only show the "BOTH" positions
    /// - for Hedge Mode user, the response will show "BOTH", "LONG", and "SHORT" positions.
    /// **Note** > Please use with user data stream `ACCOUNT_UPDATE` to meet your timeliness and
    /// accuracy needs.
    /// - Please use with user data stream ACCOUNT_UPDATE to meet your timeliness and accuracy
    /// needs.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#position-information
    [[nodiscard]] common::RestApiResponse<std::vector<PositionInformationResponseInner>>
    position_information(const PositionInformationParams& params = {}) const;

    /// Asynchronous `position_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<PositionInformationResponseInner>>)`.
    template <class CompletionToken>
    auto async_position_information(const PositionInformationParams& params,
                                    CompletionToken&& token) const {
        return common::async_send<std::vector<PositionInformationResponseInner>>(
            client_, position_information_request(params), std::forward<CompletionToken>(token));
    }

    /// Query Current Open Order (USER_DATA)
    ///
    /// GET /dapi/v1/openOrder.
    ///
    /// Query Current Open Order
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either`orderId` or `origClientOrderId` must be sent
    /// - If the queried order has been filled or cancelled, the error message "Order does not
    /// exist" will be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#query-current-open-order
    [[nodiscard]] common::RestApiResponse<QueryCurrentOpenOrderResponse>
    query_current_open_order(const QueryCurrentOpenOrderParams& params) const;

    /// Asynchronous `query_current_open_order()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryCurrentOpenOrderResponse>)`.
    template <class CompletionToken>
    auto async_query_current_open_order(const QueryCurrentOpenOrderParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<QueryCurrentOpenOrderResponse>(
            client_, query_current_open_order_request(params),
            std::forward<CompletionToken>(token));
    }

    /// User's Force Orders (USER_DATA)
    ///
    /// GET /dapi/v1/forceOrders.
    ///
    /// User's Force Orders
    ///
    /// Weight: **20** (after CM migration: **20** with symbol / **50** without symbol)
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If "autoCloseType" is not sent, orders with both of the types will be returned
    /// - Only support querying data in the past 90 days
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/trade#users-force-orders
    [[nodiscard]] common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>
    users_force_orders(const UsersForceOrdersParams& params = {}) const;

    /// Asynchronous `users_force_orders()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<UsersForceOrdersResponseInner>>)`.
    template <class CompletionToken>
    auto async_users_force_orders(const UsersForceOrdersParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<UsersForceOrdersResponseInner>>(
            client_, users_force_orders_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    account_trade_list_request(const AccountTradeListParams& params) const;
    [[nodiscard]] common::RestRequest all_orders_request(const AllOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    auto_cancel_all_open_orders_request(const AutoCancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_all_open_orders_request(const CancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    cancel_multiple_orders_request(const CancelMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_multiple_orders_request(const ModifyMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    place_multiple_orders_request(const PlaceMultipleOrdersParams& params) const;
    [[nodiscard]] common::RestRequest cancel_order_request(const CancelOrderParams& params) const;
    [[nodiscard]] common::RestRequest modify_order_request(const ModifyOrderParams& params) const;
    [[nodiscard]] common::RestRequest new_order_request(const NewOrderParams& params) const;
    [[nodiscard]] common::RestRequest query_order_request(const QueryOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    change_initial_leverage_request(const ChangeInitialLeverageParams& params) const;
    [[nodiscard]] common::RestRequest
    change_margin_type_request(const ChangeMarginTypeParams& params) const;
    [[nodiscard]] common::RestRequest
    change_position_mode_request(const ChangePositionModeParams& params) const;
    [[nodiscard]] common::RestRequest
    current_all_open_orders_request(const CurrentAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    get_order_modify_history_request(const GetOrderModifyHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_position_margin_change_history_request(
        const GetPositionMarginChangeHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    modify_isolated_position_margin_request(const ModifyIsolatedPositionMarginParams& params) const;
    [[nodiscard]] common::RestRequest position_adl_quantile_estimation_request(
        const PositionAdlQuantileEstimationParams& params) const;
    [[nodiscard]] common::RestRequest
    position_information_request(const PositionInformationParams& params) const;
    [[nodiscard]] common::RestRequest
    query_current_open_order_request(const QueryCurrentOpenOrderParams& params) const;
    [[nodiscard]] common::RestRequest
    users_force_orders_request(const UsersForceOrdersParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_coin_futures::rest_api
