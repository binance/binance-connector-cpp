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
#include <binance/derivatives_trading_coin_futures/export.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/basis_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/check_server_time_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/compressed_aggregate_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/continuous_contract_kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/exchange_information_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_funding_rate_history_of_perpetual_futures_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/get_funding_rate_info_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/index_price_and_mark_price_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/index_price_kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/long_short_ratio_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/old_trades_lookup_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/open_interest_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/open_interest_statistics_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/order_book_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/premium_index_kline_data_item_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/query_index_price_constituents_response.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/recent_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/symbol_order_book_ticker_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/symbol_price_ticker_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/taker_buy_sell_volume_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/ticker24hr_price_change_statistics_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/top_trader_long_short_ratio_accounts_response_inner.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/models/top_trader_long_short_ratio_positions_response_inner.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

enum class BasisContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(BasisContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT BasisContractTypeEnum
tag_invoke(boost::json::value_to_tag<BasisContractTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                BasisContractTypeEnum value);

enum class BasisPeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(BasisPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT BasisPeriodEnum
tag_invoke(boost::json::value_to_tag<BasisPeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, BasisPeriodEnum value);

enum class ContinuousContractKlineCandlestickDataContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickDataContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT
ContinuousContractKlineCandlestickDataContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickDataContractTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickDataContractTypeEnum value);

enum class ContinuousContractKlineCandlestickDataIntervalEnum {
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT ContinuousContractKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickDataIntervalEnum value);

enum class IndexPriceKlineCandlestickDataIntervalEnum {
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(IndexPriceKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT IndexPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<IndexPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           IndexPriceKlineCandlestickDataIntervalEnum value);

enum class KlineCandlestickDataIntervalEnum {
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(KlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT KlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           KlineCandlestickDataIntervalEnum value);

enum class LongShortRatioPeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(LongShortRatioPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT LongShortRatioPeriodEnum tag_invoke(
    boost::json::value_to_tag<LongShortRatioPeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                LongShortRatioPeriodEnum value);

enum class LongShortRatioContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(LongShortRatioContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT LongShortRatioContractTypeEnum
tag_invoke(boost::json::value_to_tag<LongShortRatioContractTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           LongShortRatioContractTypeEnum value);

enum class MarkPriceKlineCandlestickDataIntervalEnum {
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(MarkPriceKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarkPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           MarkPriceKlineCandlestickDataIntervalEnum value);

enum class OpenInterestStatisticsPeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(OpenInterestStatisticsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT OpenInterestStatisticsPeriodEnum
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           OpenInterestStatisticsPeriodEnum value);

enum class OpenInterestStatisticsContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(OpenInterestStatisticsContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT OpenInterestStatisticsContractTypeEnum
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsContractTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           OpenInterestStatisticsContractTypeEnum value);

enum class PremiumIndexKlineDataIntervalEnum {
    Interval1m,
    Interval3m,
    Interval5m,
    Interval15m,
    Interval30m,
    Interval1h,
    Interval2h,
    Interval4h,
    Interval6h,
    Interval8h,
    Interval12h,
    Interval1d,
    Interval3d,
    Interval1w,
    Interval1Month,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(PremiumIndexKlineDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT PremiumIndexKlineDataIntervalEnum
tag_invoke(boost::json::value_to_tag<PremiumIndexKlineDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PremiumIndexKlineDataIntervalEnum value);

enum class TakerBuySellVolumeContractTypeEnum {
    All,
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TakerBuySellVolumeContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TakerBuySellVolumeContractTypeEnum
tag_invoke(boost::json::value_to_tag<TakerBuySellVolumeContractTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TakerBuySellVolumeContractTypeEnum value);

enum class TakerBuySellVolumePeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TakerBuySellVolumePeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TakerBuySellVolumePeriodEnum tag_invoke(
    boost::json::value_to_tag<TakerBuySellVolumePeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                TakerBuySellVolumePeriodEnum value);

enum class TopTraderLongShortRatioAccountsPeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioAccountsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TopTraderLongShortRatioAccountsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioAccountsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioAccountsPeriodEnum value);

enum class TopTraderLongShortRatioAccountsContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioAccountsContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TopTraderLongShortRatioAccountsContractTypeEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioAccountsContractTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioAccountsContractTypeEnum value);

enum class TopTraderLongShortRatioPositionsPeriodEnum {
    Period5m,
    Period15m,
    Period30m,
    Period1h,
    Period2h,
    Period4h,
    Period6h,
    Period12h,
    Period1d,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioPositionsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TopTraderLongShortRatioPositionsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioPositionsPeriodEnum value);

enum class TopTraderLongShortRatioPositionsContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioPositionsContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT TopTraderLongShortRatioPositionsContractTypeEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsContractTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioPositionsContractTypeEnum value);

struct BasisParams {
    /// Pair.
    common::Required<std::string> pair;
    /// Contract type.
    common::Required<BasisContractTypeEnum> contract_type;
    /// Period interval.
    common::Required<BasisPeriodEnum> period;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct CompressedAggregateTradesListParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// ID to get aggregate trades from INCLUSIVE.
    std::optional<std::int64_t> from_id = std::nullopt;
    /// Timestamp in ms to get aggregate trades from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get aggregate trades until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct ContinuousContractKlineCandlestickDataParams {
    /// After CM migration, accepts both CM and UM pair values.
    common::Required<std::string> pair;
    common::Required<ContinuousContractKlineCandlestickDataContractTypeEnum> contract_type;
    /// Interval
    common::Required<ContinuousContractKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct GetFundingRateHistoryOfPerpetualFuturesParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Timestamp in ms to get funding rate from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding rate until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct IndexPriceAndMarkPriceParams {
    std::optional<std::string> symbol = std::nullopt;
    std::optional<std::string> pair = std::nullopt;
};

struct IndexPriceKlineCandlestickDataParams {
    /// After CM migration, accepts both CM and UM pair values.
    common::Required<std::string> pair;
    /// Interval
    common::Required<IndexPriceKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct KlineCandlestickDataParams {
    /// After CM migration, accepts both CM and UM symbols.
    common::Required<std::string> symbol;
    /// Interval
    common::Required<KlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct LongShortRatioParams {
    /// BTCUSD
    common::Required<std::string> pair;
    common::Required<LongShortRatioPeriodEnum> period;
    /// Contract type filter. If omitted, returns aggregated data across all contract types.
    std::optional<LongShortRatioContractTypeEnum> contract_type = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct MarkPriceKlineCandlestickDataParams {
    /// After CM migration, accepts both CM and UM symbols.
    common::Required<std::string> symbol;
    /// Interval
    common::Required<MarkPriceKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct OldTradesLookupParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    /// TradeId to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
};

struct OpenInterestParams {
    /// Symbol
    common::Required<std::string> symbol;
};

struct OpenInterestStatisticsParams {
    common::Required<std::string> pair;
    common::Required<OpenInterestStatisticsPeriodEnum> period;
    /// Contract type filter. If omitted, returns aggregated data across all contract types.
    std::optional<OpenInterestStatisticsContractTypeEnum> contract_type = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct OrderBookParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Valid limits:[5, 10, 20, 50, 100, 500, 1000].
    std::optional<std::int64_t> limit = std::nullopt;
};

struct PremiumIndexKlineDataParams {
    /// After CM migration, accepts both CM and UM symbols.
    common::Required<std::string> symbol;
    /// Interval
    common::Required<PremiumIndexKlineDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct QueryIndexPriceConstituentsParams {
    /// Symbol
    common::Required<std::string> symbol;
};

struct RecentTradesListParams {
    /// Symbol
    common::Required<std::string> symbol;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
};

struct SymbolOrderBookTickerParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Symbol
    std::optional<std::string> pair = std::nullopt;
};

struct SymbolPriceTickerParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Pair
    std::optional<std::string> pair = std::nullopt;
};

struct TakerBuySellVolumeParams {
    common::Required<std::string> pair;
    common::Required<TakerBuySellVolumeContractTypeEnum> contract_type;
    common::Required<TakerBuySellVolumePeriodEnum> period;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct Ticker24hrPriceChangeStatisticsParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Pair
    std::optional<std::string> pair = std::nullopt;
};

struct TopTraderLongShortRatioAccountsParams {
    /// Pair
    common::Required<std::string> pair;
    common::Required<TopTraderLongShortRatioAccountsPeriodEnum> period;
    /// Contract type filter. If omitted, returns aggregated data across all contract types.
    std::optional<TopTraderLongShortRatioAccountsContractTypeEnum> contract_type = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct TopTraderLongShortRatioPositionsParams {
    common::Required<std::string> pair;
    common::Required<TopTraderLongShortRatioPositionsPeriodEnum> period;
    /// Contract type filter. If omitted, returns aggregated data across all contract types.
    std::optional<TopTraderLongShortRatioPositionsContractTypeEnum> contract_type = std::nullopt;
    /// Maximum number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_COIN_FUTURES_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Basis
    ///
    /// GET /futures/data/basis.
    ///
    /// Query basis
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#basis
    [[nodiscard]] common::RestApiResponse<std::vector<BasisResponseInner>>
    basis(const BasisParams& params) const;

    /// Asynchronous `basis()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<BasisResponseInner>>)`.
    template <class CompletionToken>
    auto async_basis(const BasisParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<BasisResponseInner>>(
            client_, basis_request(params), std::forward<CompletionToken>(token));
    }

    /// Check Server time
    ///
    /// GET /dapi/v1/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#check-server-time
    [[nodiscard]] common::RestApiResponse<CheckServerTimeResponse> check_server_time() const;

    /// Asynchronous `check_server_time()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckServerTimeResponse>)`.
    template <class CompletionToken> auto async_check_server_time(CompletionToken&& token) const {
        return common::async_send<CheckServerTimeResponse>(client_, check_server_time_request(),
                                                           std::forward<CompletionToken>(token));
    }

    /// Compressed/Aggregate Trades List
    ///
    /// GET /dapi/v1/aggTrades.
    ///
    /// Get compressed, aggregate trades. Market trades that fill in 100ms with
    /// the same price and the same taking side will have the quantity
    /// aggregated.
    ///
    /// Weight(IP): 20
    ///
    /// Notes:
    /// - only trade histories within the past 48 hours (counted from now) can be queried
    /// - If both `startTime` and `endTime` are sent, time between `startTime` and `endTime` must be
    /// less than 1 hour.
    /// - If `fromId`, `startTime`, and `endTime` are not sent, the most recent aggregate trades
    /// will be returned.
    /// - Only market trades will be aggregated and returned, which means the insurance fund trades
    /// and ADL trades won't be aggregated.
    /// - Sending both `startTime`/`endTime` and `fromId` might cause response timeout, please send
    /// either `fromId` or `startTime`/`endTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#compressed-aggregate-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<CompressedAggregateTradesListResponseInner>>
    compressed_aggregate_trades_list(const CompressedAggregateTradesListParams& params) const;

    /// Asynchronous `compressed_aggregate_trades_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CompressedAggregateTradesListResponseInner>>)`.
    template <class CompletionToken>
    auto async_compressed_aggregate_trades_list(const CompressedAggregateTradesListParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<std::vector<CompressedAggregateTradesListResponseInner>>(
            client_, compressed_aggregate_trades_list_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Continuous Contract Kline/Candlestick Data
    ///
    /// GET /dapi/v1/continuousKlines.
    ///
    /// Kline/candlestick bars for a specific contract type. Klines are uniquely identified by their
    /// open time.
    ///
    /// Weight: based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#continuous-contract-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
    continuous_contract_kline_candlestick_data(
        const ContinuousContractKlineCandlestickDataParams& params) const;

    /// Asynchronous `continuous_contract_kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_continuous_contract_kline_candlestick_data(
        const ContinuousContractKlineCandlestickDataParams& params, CompletionToken&& token) const {
        return common::async_send<
            std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>(
            client_, continuous_contract_kline_candlestick_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Exchange Information
    ///
    /// GET /dapi/v1/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#exchange-information
    [[nodiscard]] common::RestApiResponse<ExchangeInformationResponse> exchange_information() const;

    /// Asynchronous `exchange_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExchangeInformationResponse>)`.
    template <class CompletionToken>
    auto async_exchange_information(CompletionToken&& token) const {
        return common::async_send<ExchangeInformationResponse>(
            client_, exchange_information_request(), std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate History of Perpetual Futures
    ///
    /// GET /dapi/v1/fundingRate.
    ///
    /// Get Funding Rate History of Perpetual Futures
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - empty array will be returned for delivery symbols.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#get-funding-rate-history-of-perpetual-futures
    [[nodiscard]] common::RestApiResponse<
        std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>
    get_funding_rate_history_of_perpetual_futures(
        const GetFundingRateHistoryOfPerpetualFuturesParams& params) const;

    /// Asynchronous `get_funding_rate_history_of_perpetual_futures()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_funding_rate_history_of_perpetual_futures(
        const GetFundingRateHistoryOfPerpetualFuturesParams& params,
        CompletionToken&& token) const {
        return common::async_send<
            std::vector<GetFundingRateHistoryOfPerpetualFuturesResponseInner>>(
            client_, get_funding_rate_history_of_perpetual_futures_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate Info
    ///
    /// GET /dapi/v1/fundingInfo.
    ///
    /// Query funding rate info for symbols that had
    /// FundingRateCap/FundingRateFloor/fundingIntervalHours adjustment
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#get-funding-rate-info
    [[nodiscard]] common::RestApiResponse<std::vector<GetFundingRateInfoResponseInner>>
    get_funding_rate_info() const;

    /// Asynchronous `get_funding_rate_info()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetFundingRateInfoResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_funding_rate_info(CompletionToken&& token) const {
        return common::async_send<std::vector<GetFundingRateInfoResponseInner>>(
            client_, get_funding_rate_info_request(), std::forward<CompletionToken>(token));
    }

    /// Index Price and Mark Price
    ///
    /// GET /dapi/v1/premiumIndex.
    ///
    /// Query index price and mark price
    ///
    /// Weight(IP): 10
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#index-price-and-mark-price
    [[nodiscard]] common::RestApiResponse<std::vector<IndexPriceAndMarkPriceResponseInner>>
    index_price_and_mark_price(const IndexPriceAndMarkPriceParams& params = {}) const;

    /// Asynchronous `index_price_and_mark_price()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<IndexPriceAndMarkPriceResponseInner>>)`.
    template <class CompletionToken>
    auto async_index_price_and_mark_price(const IndexPriceAndMarkPriceParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<std::vector<IndexPriceAndMarkPriceResponseInner>>(
            client_, index_price_and_mark_price_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Index Price Kline/Candlestick Data
    ///
    /// GET /dapi/v1/indexPriceKlines.
    ///
    /// Kline/candlestick bars for the index price of a pair. Klines are uniquely identified by
    /// their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#index-price-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
    index_price_kline_candlestick_data(const IndexPriceKlineCandlestickDataParams& params) const;

    /// Asynchronous `index_price_kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto
    async_index_price_kline_candlestick_data(const IndexPriceKlineCandlestickDataParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<
            std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>(
            client_, index_price_kline_candlestick_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Kline/Candlestick Data
    ///
    /// GET /dapi/v1/klines.
    ///
    /// Kline/candlestick bars for a symbol. Klines are uniquely identified by their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>
    kline_candlestick_data(const KlineCandlestickDataParams& params) const;

    /// Asynchronous `kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_kline_candlestick_data(const KlineCandlestickDataParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<
            std::vector<std::vector<ContinuousContractKlineCandlestickDataItemInner>>>(
            client_, kline_candlestick_data_request(params), std::forward<CompletionToken>(token));
    }

    /// Long/Short Ratio
    ///
    /// GET /futures/data/globalLongShortAccountRatio.
    ///
    /// Query symbol Long/Short Ratio
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#long-short-ratio
    [[nodiscard]] common::RestApiResponse<std::vector<LongShortRatioResponseInner>>
    long_short_ratio(const LongShortRatioParams& params) const;

    /// Asynchronous `long_short_ratio()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<LongShortRatioResponseInner>>)`.
    template <class CompletionToken>
    auto async_long_short_ratio(const LongShortRatioParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<LongShortRatioResponseInner>>(
            client_, long_short_ratio_request(params), std::forward<CompletionToken>(token));
    }

    /// Mark Price Kline/Candlestick Data
    ///
    /// GET /dapi/v1/markPriceKlines.
    ///
    /// Kline/candlestick bars for the mark price of a symbol. Klines are uniquely identified by
    /// their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT | weight |
    /// | --- | --- |
    /// | [1,100) | 1 |
    /// | [100, 500) | 2 |
    /// | [500, 1000] | 5 |
    /// | > 1000 | 10 |
    ///
    /// Notes:
    /// - The difference between `startTime` and `endTime` can only be up to 200 days
    /// - Between `startTime` and `endTime`, the most recent `limit` data from `endTime` will be
    /// returned:
    ///   - If `startTime` and `endTime` are not sent, current timestamp will be set as `endTime`,
    ///   and the most recent data will be returned.
    ///   - If `startTime` is sent only, the timestamp of 200 days after `startTime` will be set as
    ///   `endTime`(up to the current time)
    ///   - If `endTime` is sent only, the timestamp of 200 days before `endTime` will be set as
    ///   `startTime`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#mark-price-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>
    mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params) const;

    /// Asynchronous `mark_price_kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<
            std::vector<std::vector<IndexPriceKlineCandlestickDataItemInner>>>(
            client_, mark_price_kline_candlestick_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Old Trades Lookup (MARKET_DATA)
    ///
    /// GET /dapi/v1/historicalTrades.
    ///
    /// Get older market historical trades.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// - Market trades means trades filled in the order book. Only market trades will be returned,
    /// which means the insurance fund trades and ADL trades won't be returned.
    /// - Only supports data from within the last one month
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#old-trades-lookup
    [[nodiscard]] common::RestApiResponse<std::vector<OldTradesLookupResponseInner>>
    old_trades_lookup(const OldTradesLookupParams& params) const;

    /// Asynchronous `old_trades_lookup()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OldTradesLookupResponseInner>>)`.
    template <class CompletionToken>
    auto async_old_trades_lookup(const OldTradesLookupParams& params,
                                 CompletionToken&& token) const {
        return common::async_send<std::vector<OldTradesLookupResponseInner>>(
            client_, old_trades_lookup_request(params), std::forward<CompletionToken>(token));
    }

    /// Open Interest
    ///
    /// GET /dapi/v1/openInterest.
    ///
    /// Get present open interest of a specific symbol.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#open-interest
    [[nodiscard]] common::RestApiResponse<OpenInterestResponse>
    open_interest(const OpenInterestParams& params) const;

    /// Asynchronous `open_interest()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OpenInterestResponse>)`.
    template <class CompletionToken>
    auto async_open_interest(const OpenInterestParams& params, CompletionToken&& token) const {
        return common::async_send<OpenInterestResponse>(client_, open_interest_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Open Interest Statistics
    ///
    /// GET /futures/data/openInterestHist.
    ///
    /// Query open interest stats
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#open-interest-statistics
    [[nodiscard]] common::RestApiResponse<std::vector<OpenInterestStatisticsResponseInner>>
    open_interest_statistics(const OpenInterestStatisticsParams& params) const;

    /// Asynchronous `open_interest_statistics()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<OpenInterestStatisticsResponseInner>>)`.
    template <class CompletionToken>
    auto async_open_interest_statistics(const OpenInterestStatisticsParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<OpenInterestStatisticsResponseInner>>(
            client_, open_interest_statistics_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Order Book
    ///
    /// GET /dapi/v1/depth.
    ///
    /// Query orderbook on specific symbol
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// | Limit | Weight |
    /// | ------------ | ------------ |
    /// | 5, 10, 20, 50 | 2 |
    /// | 100 | 5 |
    /// | 500 | 10 |
    /// | 1000 | 20 |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#order-book
    [[nodiscard]] common::RestApiResponse<OrderBookResponse>
    order_book(const OrderBookParams& params) const;

    /// Asynchronous `order_book()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderBookResponse>)`.
    template <class CompletionToken>
    auto async_order_book(const OrderBookParams& params, CompletionToken&& token) const {
        return common::async_send<OrderBookResponse>(client_, order_book_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Premium index Kline Data
    ///
    /// GET /dapi/v1/premiumIndexKlines.
    ///
    /// Premium index kline bars of a symbol. Klines are uniquely identified by their open time.
    ///
    /// Weight: Based on parameter `LIMIT`
    ///
    /// | LIMIT       | weight |
    /// | ----------- | ------ |
    /// | [1,100)     | 1      |
    /// | [100, 500)  | 2      |
    /// | [500, 1000] | 5      |
    /// | > 1000      | 10     |
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent klines are returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#premium-index-kline-data
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>
    premium_index_kline_data(const PremiumIndexKlineDataParams& params) const;

    /// Asynchronous `premium_index_kline_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_premium_index_kline_data(const PremiumIndexKlineDataParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<PremiumIndexKlineDataItemInner>>>(
            client_, premium_index_kline_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Index Price Constituents
    ///
    /// GET /dapi/v1/constituents.
    ///
    /// Query index price constituents
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#query-index-price-constituents
    [[nodiscard]] common::RestApiResponse<QueryIndexPriceConstituentsResponse>
    query_index_price_constituents(const QueryIndexPriceConstituentsParams& params) const;

    /// Asynchronous `query_index_price_constituents()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryIndexPriceConstituentsResponse>)`.
    template <class CompletionToken>
    auto async_query_index_price_constituents(const QueryIndexPriceConstituentsParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<QueryIndexPriceConstituentsResponse>(
            client_, query_index_price_constituents_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Recent Trades List
    ///
    /// GET /dapi/v1/trades.
    ///
    /// Get recent market trades
    ///
    /// Weight(IP): 5
    ///
    /// Notes:
    /// - Market trades means trades filled in the order book. Only market trades will be returned,
    /// which means the insurance fund trades and ADL trades won't be returned.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#recent-trades-list
    [[nodiscard]] common::RestApiResponse<std::vector<RecentTradesListResponseInner>>
    recent_trades_list(const RecentTradesListParams& params) const;

    /// Asynchronous `recent_trades_list()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<RecentTradesListResponseInner>>)`.
    template <class CompletionToken>
    auto async_recent_trades_list(const RecentTradesListParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<std::vector<RecentTradesListResponseInner>>(
            client_, recent_trades_list_request(params), std::forward<CompletionToken>(token));
    }

    /// Symbol Order Book Ticker
    ///
    /// GET /dapi/v1/ticker/bookTicker.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// Weight: **2** for a single symbol, **5** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#symbol-order-book-ticker
    [[nodiscard]] common::RestApiResponse<std::vector<SymbolOrderBookTickerResponseInner>>
    symbol_order_book_ticker(const SymbolOrderBookTickerParams& params = {}) const;

    /// Asynchronous `symbol_order_book_ticker()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<SymbolOrderBookTickerResponseInner>>)`.
    template <class CompletionToken>
    auto async_symbol_order_book_ticker(const SymbolOrderBookTickerParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<SymbolOrderBookTickerResponseInner>>(
            client_, symbol_order_book_ticker_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Symbol Price Ticker
    ///
    /// GET /dapi/v1/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: **1** for a single symbol, **2** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#symbol-price-ticker
    [[nodiscard]] common::RestApiResponse<std::vector<SymbolPriceTickerResponseInner>>
    symbol_price_ticker(const SymbolPriceTickerParams& params = {}) const;

    /// Asynchronous `symbol_price_ticker()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<SymbolPriceTickerResponseInner>>)`.
    template <class CompletionToken>
    auto async_symbol_price_ticker(const SymbolPriceTickerParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<std::vector<SymbolPriceTickerResponseInner>>(
            client_, symbol_price_ticker_request(params), std::forward<CompletionToken>(token));
    }

    /// Taker Buy/Sell Volume
    ///
    /// GET /futures/data/takerBuySellVol.
    ///
    /// Taker Buy Volume: the total volume of buy orders filled by takers within
    /// the period.
    ///
    /// Taker Sell Volume: the total volume of sell orders filled by takers
    /// within the period.
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#taker-buy-sell-volume
    [[nodiscard]] common::RestApiResponse<std::vector<TakerBuySellVolumeResponseInner>>
    taker_buy_sell_volume(const TakerBuySellVolumeParams& params) const;

    /// Asynchronous `taker_buy_sell_volume()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<TakerBuySellVolumeResponseInner>>)`.
    template <class CompletionToken>
    auto async_taker_buy_sell_volume(const TakerBuySellVolumeParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<std::vector<TakerBuySellVolumeResponseInner>>(
            client_, taker_buy_sell_volume_request(params), std::forward<CompletionToken>(token));
    }

    /// Test Connectivity
    ///
    /// GET /dapi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const;

    /// Asynchronous `test_connectivity()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, test_connectivity_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// 24hr Ticker Price Change Statistics
    ///
    /// GET /dapi/v1/ticker/24hr.
    ///
    /// 24 hour rolling window price change statistics.
    ///
    /// Weight: **1** for a single symbol, **40** when the symbol parameter is omitted
    /// **Careful** when accessing this with no symbol.
    ///
    /// Notes:
    /// - Symbol and pair cannot be sent together
    /// - If a pair is sent,tickers for all symbols of the pair will be returned
    /// - If either a pair or symbol is sent, tickers for all symbols of all pairs will be returned
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#ticker24hr-price-change-statistics
    [[nodiscard]] common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>
    ticker24hr_price_change_statistics(
        const Ticker24hrPriceChangeStatisticsParams& params = {}) const;

    /// Asynchronous `ticker24hr_price_change_statistics()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_ticker24hr_price_change_statistics(const Ticker24hrPriceChangeStatisticsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>(
            client_, ticker24hr_price_change_statistics_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Top Trader Long/Short Account Ratio
    ///
    /// GET /futures/data/topLongShortAccountRatio.
    ///
    /// The proportion of net long and net short accounts to total accounts of
    /// the top 20% users with the highest margin balance. Each account is
    /// counted once only.
    ///
    /// Long Account % = Accounts of top traders with net long positions / Total
    /// accounts of top traders with open positions
    ///
    /// Short Account % = Accounts of top traders with net short positions /
    /// Total accounts of top traders with open positions
    ///
    /// Long/Short Ratio (Accounts) = Long Account % / Short Account %
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: Accounts
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-accounts
    [[nodiscard]] common::RestApiResponse<std::vector<TopTraderLongShortRatioAccountsResponseInner>>
    top_trader_long_short_ratio_accounts(const TopTraderLongShortRatioAccountsParams& params) const;

    /// Asynchronous `top_trader_long_short_ratio_accounts()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<TopTraderLongShortRatioAccountsResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_top_trader_long_short_ratio_accounts(const TopTraderLongShortRatioAccountsParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<TopTraderLongShortRatioAccountsResponseInner>>(
            client_, top_trader_long_short_ratio_accounts_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Top Trader Long/Short Position Ratio
    ///
    /// GET /futures/data/topLongShortPositionRatio.
    ///
    /// The proportion of net long and net short positions to total open
    /// positions of the top 20% users with the highest margin balance.
    ///
    /// Long Position % = Long positions of top traders / Total open positions
    /// of top traders
    ///
    /// Short Position % = Short positions of top traders / Total open positions
    /// of top traders
    ///
    /// Long/Short Ratio (Positions) = Long Position % / Short Position %
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: Positions
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-coin-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-positions
    [[nodiscard]] common::RestApiResponse<
        std::vector<TopTraderLongShortRatioPositionsResponseInner>>
    top_trader_long_short_ratio_positions(
        const TopTraderLongShortRatioPositionsParams& params) const;

    /// Asynchronous `top_trader_long_short_ratio_positions()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<TopTraderLongShortRatioPositionsResponseInner>>)`.
    template <class CompletionToken>
    auto async_top_trader_long_short_ratio_positions(
        const TopTraderLongShortRatioPositionsParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<TopTraderLongShortRatioPositionsResponseInner>>(
            client_, top_trader_long_short_ratio_positions_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest basis_request(const BasisParams& params) const;
    [[nodiscard]] common::RestRequest check_server_time_request() const;
    [[nodiscard]] common::RestRequest compressed_aggregate_trades_list_request(
        const CompressedAggregateTradesListParams& params) const;
    [[nodiscard]] common::RestRequest continuous_contract_kline_candlestick_data_request(
        const ContinuousContractKlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest exchange_information_request() const;
    [[nodiscard]] common::RestRequest get_funding_rate_history_of_perpetual_futures_request(
        const GetFundingRateHistoryOfPerpetualFuturesParams& params) const;
    [[nodiscard]] common::RestRequest get_funding_rate_info_request() const;
    [[nodiscard]] common::RestRequest
    index_price_and_mark_price_request(const IndexPriceAndMarkPriceParams& params) const;
    [[nodiscard]] common::RestRequest index_price_kline_candlestick_data_request(
        const IndexPriceKlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest
    kline_candlestick_data_request(const KlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest
    long_short_ratio_request(const LongShortRatioParams& params) const;
    [[nodiscard]] common::RestRequest mark_price_kline_candlestick_data_request(
        const MarkPriceKlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest
    old_trades_lookup_request(const OldTradesLookupParams& params) const;
    [[nodiscard]] common::RestRequest open_interest_request(const OpenInterestParams& params) const;
    [[nodiscard]] common::RestRequest
    open_interest_statistics_request(const OpenInterestStatisticsParams& params) const;
    [[nodiscard]] common::RestRequest order_book_request(const OrderBookParams& params) const;
    [[nodiscard]] common::RestRequest
    premium_index_kline_data_request(const PremiumIndexKlineDataParams& params) const;
    [[nodiscard]] common::RestRequest
    query_index_price_constituents_request(const QueryIndexPriceConstituentsParams& params) const;
    [[nodiscard]] common::RestRequest
    recent_trades_list_request(const RecentTradesListParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_order_book_ticker_request(const SymbolOrderBookTickerParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_price_ticker_request(const SymbolPriceTickerParams& params) const;
    [[nodiscard]] common::RestRequest
    taker_buy_sell_volume_request(const TakerBuySellVolumeParams& params) const;
    [[nodiscard]] common::RestRequest test_connectivity_request() const;
    [[nodiscard]] common::RestRequest ticker24hr_price_change_statistics_request(
        const Ticker24hrPriceChangeStatisticsParams& params) const;
    [[nodiscard]] common::RestRequest top_trader_long_short_ratio_accounts_request(
        const TopTraderLongShortRatioAccountsParams& params) const;
    [[nodiscard]] common::RestRequest top_trader_long_short_ratio_positions_request(
        const TopTraderLongShortRatioPositionsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_coin_futures::rest_api
