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
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/adl_risk_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/asset_index_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/basis_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/check_server_time_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/composite_index_symbol_information_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/compressed_aggregate_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/continuous_contract_kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/exchange_information_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_funding_rate_history_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/get_funding_rate_info_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/index_price_kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/long_short_ratio_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/mark_price_kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/mark_price_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/old_trades_lookup_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/open_interest_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/open_interest_statistics_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/order_book_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/premium_index_kline_data_item_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/quarterly_contract_settlement_price_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_index_price_constituents_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/query_insurance_fund_balance_snapshot_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/recent_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/rpi_order_book_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_order_book_ticker_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_price_ticker_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/symbol_price_ticker_v2_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/taker_buy_sell_volume_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/ticker24hr_price_change_statistics_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/top_trader_long_short_ratio_accounts_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/top_trader_long_short_ratio_positions_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/trading_schedule_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

enum class BasisContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(BasisContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT BasisContractTypeEnum
tag_invoke(boost::json::value_to_tag<BasisContractTypeEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(BasisPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT BasisPeriodEnum
tag_invoke(boost::json::value_to_tag<BasisPeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv, BasisPeriodEnum value);

enum class ContinuousContractKlineCandlestickDataContractTypeEnum {
    Perpetual,
    CurrentQuarter,
    NextQuarter,
    TradifiPerpetual,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickDataContractTypeEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT
ContinuousContractKlineCandlestickDataContractTypeEnum tag_invoke(
    boost::json::value_to_tag<ContinuousContractKlineCandlestickDataContractTypeEnum> /*tag*/,
    const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           ContinuousContractKlineCandlestickDataContractTypeEnum value);

enum class ContinuousContractKlineCandlestickDataIntervalEnum {
    Interval1s,
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(ContinuousContractKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ContinuousContractKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<ContinuousContractKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(IndexPriceKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT IndexPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<IndexPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(KlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT KlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(LongShortRatioPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT LongShortRatioPeriodEnum tag_invoke(
    boost::json::value_to_tag<LongShortRatioPeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                                                boost::json::value& jv,
                                                                LongShortRatioPeriodEnum value);

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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(MarkPriceKlineCandlestickDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarkPriceKlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<MarkPriceKlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(OpenInterestStatisticsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT OpenInterestStatisticsPeriodEnum
tag_invoke(boost::json::value_to_tag<OpenInterestStatisticsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           OpenInterestStatisticsPeriodEnum value);

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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(PremiumIndexKlineDataIntervalEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PremiumIndexKlineDataIntervalEnum
tag_invoke(boost::json::value_to_tag<PremiumIndexKlineDataIntervalEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           PremiumIndexKlineDataIntervalEnum value);

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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TakerBuySellVolumePeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TakerBuySellVolumePeriodEnum tag_invoke(
    boost::json::value_to_tag<TakerBuySellVolumePeriodEnum> /*tag*/, const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioAccountsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TopTraderLongShortRatioAccountsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioAccountsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioAccountsPeriodEnum value);

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

[[nodiscard]] BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT std::string_view
to_string(TopTraderLongShortRatioPositionsPeriodEnum value) noexcept;
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT TopTraderLongShortRatioPositionsPeriodEnum
tag_invoke(boost::json::value_to_tag<TopTraderLongShortRatioPositionsPeriodEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           TopTraderLongShortRatioPositionsPeriodEnum value);

struct AdlRiskParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
};

struct AssetIndexParams {
    /// Asset pair
    std::optional<std::string> symbol = std::nullopt;
};

struct BasisParams {
    common::Required<std::string> pair;
    common::Required<BasisContractTypeEnum> contract_type;
    common::Required<BasisPeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct CompositeIndexSymbolInformationParams {
    std::optional<std::string> symbol = std::nullopt;
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
    std::optional<std::int64_t> limit = std::nullopt;
};

struct ContinuousContractKlineCandlestickDataParams {
    /// After CM migration, accepts both UM and CM pair values.
    common::Required<std::string> pair;
    /// Futurestype
    common::Required<ContinuousContractKlineCandlestickDataContractTypeEnum> contract_type;
    common::Required<ContinuousContractKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct GetFundingRateHistoryParams {
    std::optional<std::string> symbol = std::nullopt;
    /// Timestamp in ms to get funding rate from INCLUSIVE.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// Timestamp in ms to get funding rate until INCLUSIVE.
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct IndexPriceKlineCandlestickDataParams {
    /// After CM migration, accepts both UM and CM pair values.
    common::Required<std::string> pair;
    common::Required<IndexPriceKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct KlineCandlestickDataParams {
    /// After CM migration, accepts both UM and CM symbols.
    common::Required<std::string> symbol;
    common::Required<KlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct LongShortRatioParams {
    common::Required<std::string> symbol;
    common::Required<LongShortRatioPeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct MarkPriceParams {
    std::optional<std::string> symbol = std::nullopt;
};

struct MarkPriceKlineCandlestickDataParams {
    /// After CM migration, accepts both UM and CM symbols.
    common::Required<std::string> symbol;
    common::Required<MarkPriceKlineCandlestickDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct OldTradesLookupParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> limit = std::nullopt;
    /// TradeId to fetch from. Default gets most recent trades.
    std::optional<std::int64_t> from_id = std::nullopt;
};

struct OpenInterestParams {
    common::Required<std::string> symbol;
};

struct OpenInterestStatisticsParams {
    common::Required<std::string> symbol;
    common::Required<OpenInterestStatisticsPeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct OrderBookParams {
    common::Required<std::string> symbol;
    /// Valid limits:[5, 10, 20, 50, 100, 500, 1000]
    std::optional<std::int64_t> limit = std::nullopt;
};

struct PremiumIndexKlineDataParams {
    /// After CM migration, accepts both UM and CM symbols.
    common::Required<std::string> symbol;
    common::Required<PremiumIndexKlineDataIntervalEnum> interval;
    /// Start time
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct QuarterlyContractSettlementPriceParams {
    common::Required<std::string> pair;
};

struct QueryIndexPriceConstituentsParams {
    common::Required<std::string> symbol;
};

struct QueryInsuranceFundBalanceSnapshotParams {
    /// Symbol
    std::optional<std::string> symbol = std::nullopt;
};

struct RecentTradesListParams {
    common::Required<std::string> symbol;
    std::optional<std::int64_t> limit = std::nullopt;
};

struct RpiOrderBookParams {
    common::Required<std::string> symbol;
    /// Valid limits:[1000]
    std::optional<std::int64_t> limit = std::nullopt;
};

struct SymbolOrderBookTickerParams {
    std::optional<std::string> symbol = std::nullopt;
};

struct SymbolPriceTickerParams {
    std::optional<std::string> symbol = std::nullopt;
};

struct SymbolPriceTickerV2Params {
    std::optional<std::string> symbol = std::nullopt;
};

struct TakerBuySellVolumeParams {
    common::Required<std::string> symbol;
    common::Required<TakerBuySellVolumePeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct Ticker24hrPriceChangeStatisticsParams {
    std::optional<std::string> symbol = std::nullopt;
};

struct TopTraderLongShortRatioAccountsParams {
    common::Required<std::string> symbol;
    common::Required<TopTraderLongShortRatioAccountsPeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

struct TopTraderLongShortRatioPositionsParams {
    common::Required<std::string> symbol;
    common::Required<TopTraderLongShortRatioPositionsPeriodEnum> period;
    std::optional<std::int64_t> limit = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// ADL Risk
    ///
    /// GET /fapi/v1/symbolAdlRisk.
    ///
    /// Query the symbol-level ADL risk rating.
    ///
    /// The ADL risk rating measures the likelihood of ADL during liquidation,
    /// and the rating takes into account the insurance fund balance, position
    /// concentration on the symbol, order book depth, price volatility, average
    /// leverage, unrealized PnL, and margin utilization at the symbol level.
    ///
    /// The rating can be high, medium and low, and is updated every 30 minutes.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#adl-risk
    [[nodiscard]] common::RestApiResponse<AdlRiskResponse>
    adl_risk(const AdlRiskParams& params = {}) const;

    /// Asynchronous `adl_risk()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AdlRiskResponse>)`.
    template <class CompletionToken>
    auto async_adl_risk(const AdlRiskParams& params, CompletionToken&& token) const {
        return common::async_send<AdlRiskResponse>(client_, adl_risk_request(params),
                                                   std::forward<CompletionToken>(token));
    }

    /// Multi-Assets Mode Asset Index
    ///
    /// GET /fapi/v1/assetIndex.
    ///
    /// Asset index price.
    ///
    /// > **CM-UM Integration (Effective 2026-06-30):** Renamed from *Multi-Assets Mode Asset
    /// Index*. The response now additionally pushes COIN-M settlement-asset price index entries
    /// (e.g., `BTCUSD`, `ETHUSD`, `BNBUSD`). The endpoint path `/fapi/v1/assetIndex` is unchanged.
    ///
    /// Weight: **1** for a single symbol; **10** when the symbol parameter is omitted
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#asset-index
    [[nodiscard]] common::RestApiResponse<AssetIndexResponse>
    asset_index(const AssetIndexParams& params = {}) const;

    /// Asynchronous `asset_index()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AssetIndexResponse>)`.
    template <class CompletionToken>
    auto async_asset_index(const AssetIndexParams& params, CompletionToken&& token) const {
        return common::async_send<AssetIndexResponse>(client_, asset_index_request(params),
                                                      std::forward<CompletionToken>(token));
    }

    /// Basis
    ///
    /// GET /futures/data/basis.
    ///
    /// Query future basis
    ///
    /// Weight(IP): 0
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#basis
    [[nodiscard]] common::RestApiResponse<std::vector<BasisResponseInner>>
    basis(const BasisParams& params) const;

    /// Asynchronous `basis()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<std::vector<BasisResponseInner>>)`.
    template <class CompletionToken>
    auto async_basis(const BasisParams& params, CompletionToken&& token) const {
        return common::async_send<std::vector<BasisResponseInner>>(
            client_, basis_request(params), std::forward<CompletionToken>(token));
    }

    /// Check Server Time
    ///
    /// GET /fapi/v1/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#check-server-time
    [[nodiscard]] common::RestApiResponse<CheckServerTimeResponse> check_server_time() const;

    /// Asynchronous `check_server_time()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckServerTimeResponse>)`.
    template <class CompletionToken> auto async_check_server_time(CompletionToken&& token) const {
        return common::async_send<CheckServerTimeResponse>(client_, check_server_time_request(),
                                                           std::forward<CompletionToken>(token));
    }

    /// Composite Index Symbol Information
    ///
    /// GET /fapi/v1/indexInfo.
    ///
    /// Query composite index symbol information
    ///
    /// Weight(IP): 1
    ///
    /// Notes:
    /// - Only for composite index symbols
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#composite-index-symbol-information
    [[nodiscard]] common::RestApiResponse<std::vector<CompositeIndexSymbolInformationResponseInner>>
    composite_index_symbol_information(
        const CompositeIndexSymbolInformationParams& params = {}) const;

    /// Asynchronous `composite_index_symbol_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<CompositeIndexSymbolInformationResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_composite_index_symbol_information(const CompositeIndexSymbolInformationParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<std::vector<CompositeIndexSymbolInformationResponseInner>>(
            client_, composite_index_symbol_information_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Compressed/Aggregate Trades List
    ///
    /// GET /fapi/v1/aggTrades.
    ///
    /// Get compressed, aggregate market trades. Market trades that fill in
    /// 100ms with the same price and the same taking side will have the
    /// quantity aggregated.
    ///
    /// Retail Price Improvement(RPI) orders are aggregated and without special
    /// tags to be distinguished.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#compressed-aggregate-trades-list
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
    /// GET /fapi/v1/continuousKlines.
    ///
    /// Kline/candlestick bars for a specific contract type.
    /// Klines are uniquely identified by their open time.
    ///
    /// Weight: based on parameter `LIMIT`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#continuous-contract-kline-candlestick-data
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
    /// GET /fapi/v1/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#exchange-information
    [[nodiscard]] common::RestApiResponse<ExchangeInformationResponse> exchange_information() const;

    /// Asynchronous `exchange_information()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExchangeInformationResponse>)`.
    template <class CompletionToken>
    auto async_exchange_information(CompletionToken&& token) const {
        return common::async_send<ExchangeInformationResponse>(
            client_, exchange_information_request(), std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate History
    ///
    /// GET /fapi/v1/fundingRate.
    ///
    /// Get Funding Rate History
    ///
    /// Weight: When `limit` ≤ 200: share 500/5min/IP rate limit with `GET /fapi/v1/fundingInfo`
    ///
    /// When `limit` > 200: 100/5min/IP rate limit
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the most recent 200 records are returned.
    /// - If the number of data between `startTime` and `endTime` is larger than `limit`, return as
    /// `startTime` + `limit`.
    /// - In ascending order.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#get-funding-rate-history
    [[nodiscard]] common::RestApiResponse<std::vector<GetFundingRateHistoryResponseInner>>
    get_funding_rate_history(const GetFundingRateHistoryParams& params = {}) const;

    /// Asynchronous `get_funding_rate_history()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetFundingRateHistoryResponseInner>>)`.
    template <class CompletionToken>
    auto async_get_funding_rate_history(const GetFundingRateHistoryParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<std::vector<GetFundingRateHistoryResponseInner>>(
            client_, get_funding_rate_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Funding Rate Info
    ///
    /// GET /fapi/v1/fundingInfo.
    ///
    /// Query funding rate info for symbols that had FundingRateCap/FundingRateFloor /
    /// fundingIntervalHours adjustment
    ///
    /// Weight: **0**
    ///
    /// share 500/5min/IP rate limit with `GET /fapi/v1/fundingRate`
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#get-funding-rate-info
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

    /// Index Price Kline/Candlestick Data
    ///
    /// GET /fapi/v1/indexPriceKlines.
    ///
    /// Kline/candlestick bars for the index price of a pair.
    /// Klines are uniquely identified by their open time.
    ///
    /// Weight: based on parameter `LIMIT`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#index-price-kline-candlestick-data
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
    /// GET /fapi/v1/klines.
    ///
    /// Kline/candlestick bars for a symbol.
    /// Klines are uniquely identified by their open time.
    ///
    /// Weight: based on parameter `LIMIT`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>
    kline_candlestick_data(const KlineCandlestickDataParams& params) const;

    /// Asynchronous `kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_kline_candlestick_data(const KlineCandlestickDataParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<KlineCandlestickDataItemInner>>>(
            client_, kline_candlestick_data_request(params), std::forward<CompletionToken>(token));
    }

    /// Long/Short Ratio
    ///
    /// GET /futures/data/globalLongShortAccountRatio.
    ///
    /// Query symbol Long/Short Ratio
    ///
    /// Weight(IP): 0
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    /// - IP rate limit 1000 requests/5min
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#long-short-ratio
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

    /// Mark Price
    ///
    /// GET /fapi/v1/premiumIndex.
    ///
    /// Mark Price and Funding Rate
    ///
    /// Weight: **1** with symbol, **10** without symbol
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#mark-price
    [[nodiscard]] common::RestApiResponse<MarkPriceResponse>
    mark_price(const MarkPriceParams& params = {}) const;

    /// Asynchronous `mark_price()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<MarkPriceResponse>)`.
    template <class CompletionToken>
    auto async_mark_price(const MarkPriceParams& params, CompletionToken&& token) const {
        return common::async_send<MarkPriceResponse>(client_, mark_price_request(params),
                                                     std::forward<CompletionToken>(token));
    }

    /// Mark Price Kline/Candlestick Data
    ///
    /// GET /fapi/v1/markPriceKlines.
    ///
    /// Kline/candlestick bars for the mark price of a symbol.
    /// Klines are uniquely identified by their open time.
    ///
    /// Weight: based on parameter `LIMIT`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#mark-price-kline-candlestick-data
    [[nodiscard]] common::RestApiResponse<
        std::vector<std::vector<MarkPriceKlineCandlestickDataItemInner>>>
    mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params) const;

    /// Asynchronous `mark_price_kline_candlestick_data()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<std::vector<MarkPriceKlineCandlestickDataItemInner>>>)`.
    template <class CompletionToken>
    auto async_mark_price_kline_candlestick_data(const MarkPriceKlineCandlestickDataParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<std::vector<std::vector<MarkPriceKlineCandlestickDataItemInner>>>(
            client_, mark_price_kline_candlestick_data_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Old Trades Lookup (MARKET_DATA)
    ///
    /// GET /fapi/v1/historicalTrades.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#old-trades-lookup
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
    /// GET /fapi/v1/openInterest.
    ///
    /// Get present open interest of a specific symbol.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#open-interest
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
    /// Open Interest Statistics
    ///
    /// Weight(IP): 0
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 1 month is available.
    /// - IP rate limit 1000 requests/5min
    /// - A period with no trades has no record and is omitted from the response. Such gaps are
    /// expected and are not backfilled.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#open-interest-statistics
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
    /// GET /fapi/v1/depth.
    ///
    /// Query symbol orderbook
    ///
    /// Retail Price Improvement(RPI) orders are not visible and excluded in the
    /// response message.
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// | Limit         | Weight |
    /// | ------------- | ------ |
    /// | 5, 10, 20, 50 | 2      |
    /// | 100           | 5      |
    /// | 500           | 10     |
    /// | 1000          | 20     |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#order-book
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
    /// GET /fapi/v1/premiumIndexKlines.
    ///
    /// Premium index kline bars of a symbol. Klines are uniquely identified by their open time.
    ///
    /// Weight: based on parameter `LIMIT`
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#premium-index-kline-data
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

    /// Quarterly Contract Settlement Price
    ///
    /// GET /futures/data/delivery-price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight(IP): 0
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#quarterly-contract-settlement-price
    [[nodiscard]] common::RestApiResponse<
        std::vector<QuarterlyContractSettlementPriceResponseInner>>
    quarterly_contract_settlement_price(const QuarterlyContractSettlementPriceParams& params) const;

    /// Asynchronous `quarterly_contract_settlement_price()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<QuarterlyContractSettlementPriceResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_quarterly_contract_settlement_price(const QuarterlyContractSettlementPriceParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<std::vector<QuarterlyContractSettlementPriceResponseInner>>(
            client_, quarterly_contract_settlement_price_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Index Price Constituents
    ///
    /// GET /fapi/v1/constituents.
    ///
    /// Query index price constituents
    ///
    /// **Note**:
    /// Prices from constituents of TradFi perps will be hiden and displayed as -1.
    ///
    /// Weight(IP): 2
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#query-index-price-constituents
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

    /// Query Insurance Fund Balance Snapshot
    ///
    /// GET /fapi/v1/insuranceBalance.
    ///
    /// Query Insurance Fund Balance Snapshot
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#query-insurance-fund-balance-snapshot
    [[nodiscard]] common::RestApiResponse<QueryInsuranceFundBalanceSnapshotResponse>
    query_insurance_fund_balance_snapshot(
        const QueryInsuranceFundBalanceSnapshotParams& params = {}) const;

    /// Asynchronous `query_insurance_fund_balance_snapshot()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<QueryInsuranceFundBalanceSnapshotResponse>)`.
    template <class CompletionToken>
    auto async_query_insurance_fund_balance_snapshot(
        const QueryInsuranceFundBalanceSnapshotParams& params, CompletionToken&& token) const {
        return common::async_send<QueryInsuranceFundBalanceSnapshotResponse>(
            client_, query_insurance_fund_balance_snapshot_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Recent Trades List
    ///
    /// GET /fapi/v1/trades.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#recent-trades-list
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

    /// RPI Order Book
    ///
    /// GET /fapi/v1/rpiDepth.
    ///
    /// Query symbol orderbook with RPI orders
    ///
    /// RPI(Retail Price Improvement) orders are included and aggreated in the
    /// response message. Crossed price levels are hidden and invisible.
    ///
    /// Weight: Adjusted based on the limit:
    ///
    /// | Limit         | Weight |
    /// | ------------- | ------ |
    /// | 1000          | 20     |
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#rpi-order-book
    [[nodiscard]] common::RestApiResponse<RpiOrderBookResponse>
    rpi_order_book(const RpiOrderBookParams& params) const;

    /// Asynchronous `rpi_order_book()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<RpiOrderBookResponse>)`.
    template <class CompletionToken>
    auto async_rpi_order_book(const RpiOrderBookParams& params, CompletionToken&& token) const {
        return common::async_send<RpiOrderBookResponse>(client_, rpi_order_book_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Symbol Order Book Ticker
    ///
    /// GET /fapi/v1/ticker/bookTicker.
    ///
    /// Best price/qty on the order book for a symbol or symbols.
    ///
    /// Retail Price Improvement(RPI) orders are not visible and excluded in the
    /// response message.
    ///
    /// Weight: **2** for a single symbol;
    /// **5** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, bookTickers for all symbols will be returned in an array.
    /// - The field `X-MBX-USED-WEIGHT-1M` in response header is not accurate from this endpoint,
    /// please ignore.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#symbol-order-book-ticker
    [[nodiscard]] common::RestApiResponse<SymbolOrderBookTickerResponse>
    symbol_order_book_ticker(const SymbolOrderBookTickerParams& params = {}) const;

    /// Asynchronous `symbol_order_book_ticker()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SymbolOrderBookTickerResponse>)`.
    template <class CompletionToken>
    auto async_symbol_order_book_ticker(const SymbolOrderBookTickerParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<SymbolOrderBookTickerResponse>(
            client_, symbol_order_book_ticker_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Symbol Price Ticker
    ///
    /// GET /fapi/v1/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: 1 for a single symbol;
    /// 2 when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, prices for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#symbol-price-ticker
    ///
    /// Deprecated: this endpoint may be removed in a future version.
    [[nodiscard]] common::RestApiResponse<SymbolPriceTickerResponse>
    symbol_price_ticker(const SymbolPriceTickerParams& params = {}) const;

    /// Asynchronous `symbol_price_ticker()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SymbolPriceTickerResponse>)`.
    template <class CompletionToken>
    auto async_symbol_price_ticker(const SymbolPriceTickerParams& params,
                                   CompletionToken&& token) const {
        return common::async_send<SymbolPriceTickerResponse>(
            client_, symbol_price_ticker_request(params), std::forward<CompletionToken>(token));
    }

    /// Symbol Price Ticker V2
    ///
    /// GET /fapi/v2/ticker/price.
    ///
    /// Latest price for a symbol or symbols.
    ///
    /// Weight: 1 for a single symbol;
    /// 2 when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, prices for all symbols will be returned in an array.
    /// - The field `X-MBX-USED-WEIGHT-1M` in response header is not accurate from this endpoint,
    /// please ignore.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#symbol-price-ticker-v2
    [[nodiscard]] common::RestApiResponse<SymbolPriceTickerV2Response>
    symbol_price_ticker_v2(const SymbolPriceTickerV2Params& params = {}) const;

    /// Asynchronous `symbol_price_ticker_v2()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SymbolPriceTickerV2Response>)`.
    template <class CompletionToken>
    auto async_symbol_price_ticker_v2(const SymbolPriceTickerV2Params& params,
                                      CompletionToken&& token) const {
        return common::async_send<SymbolPriceTickerV2Response>(
            client_, symbol_price_ticker_v2_request(params), std::forward<CompletionToken>(token));
    }

    /// Taker Buy/Sell Volume
    ///
    /// GET /futures/data/takerlongshortRatio.
    ///
    /// Taker Buy/Sell Volume
    ///
    /// Weight(IP): 0
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    /// - IP rate limit 1000 requests/5min
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#taker-buy-sell-volume
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
    /// GET /fapi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const;

    /// Asynchronous `test_connectivity()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, test_connectivity_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// 24hr Ticker Price Change Statistics
    ///
    /// GET /fapi/v1/ticker/24hr.
    ///
    /// 24 hour rolling window price change statistics.
    /// **Careful** when accessing this with no symbol.
    ///
    /// Weight: **1** for a single symbol;
    /// **40** when the symbol parameter is omitted
    ///
    /// Notes:
    /// - If the symbol is not sent, tickers for all symbols will be returned in an array.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#ticker24hr-price-change-statistics
    [[nodiscard]] common::RestApiResponse<Ticker24hrPriceChangeStatisticsResponse>
    ticker24hr_price_change_statistics(
        const Ticker24hrPriceChangeStatisticsParams& params = {}) const;

    /// Asynchronous `ticker24hr_price_change_statistics()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<Ticker24hrPriceChangeStatisticsResponse>)`.
    template <class CompletionToken>
    auto
    async_ticker24hr_price_change_statistics(const Ticker24hrPriceChangeStatisticsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<Ticker24hrPriceChangeStatisticsResponse>(
            client_, ticker24hr_price_change_statistics_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Top Trader Long/Short Account Ratio (MARKET_DATA)
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
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    /// - IP rate limit 1000 requests/5min
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-accounts
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

    /// Top Trader Long/Short Position Ratio (MARKET_DATA)
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
    /// Weight(IP): 0
    ///
    /// Security Type: MARKET_DATA
    ///
    /// Notes:
    /// - If startTime and endTime are not sent, the most recent data is returned.
    /// - Only the data of the latest 30 days is available.
    /// - IP rate limit 1000 requests/5min
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#top-trader-long-short-ratio-positions
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

    /// Trading Schedule
    ///
    /// GET /fapi/v1/tradingSchedule.
    ///
    /// Trading session schedules for the underlying assets of TradFi Perps are provided for a
    /// one-week period forward and one-week period backward starting from the day prior to the
    /// query time, covering the U.S. equity market, Korean equity market, Hong Kong equity market,
    /// China equity market, the commodity market, and the FX market.
    ///
    /// Session types per market:
    /// - U.S. equity market: "PRE_MARKET", "REGULAR", "AFTER_MARKET", "OVERNIGHT", "NO_TRADING".
    /// - Commodity market: "REGULAR", "NO_TRADING".
    /// - Korean equity market: "REGULAR", "NO_TRADING".
    /// - Hong Kong equity market: "REGULAR", "NO_TRADING".
    /// - China equity market: "REGULAR", "NO_TRADING".
    /// - FX market: "REGULAR", "NO_TRADING".
    ///
    /// Weight(IP): 5
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/market-data#trading-schedule
    [[nodiscard]] common::RestApiResponse<TradingScheduleResponse> trading_schedule() const;

    /// Asynchronous `trading_schedule()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TradingScheduleResponse>)`.
    template <class CompletionToken> auto async_trading_schedule(CompletionToken&& token) const {
        return common::async_send<TradingScheduleResponse>(client_, trading_schedule_request(),
                                                           std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest adl_risk_request(const AdlRiskParams& params) const;
    [[nodiscard]] common::RestRequest asset_index_request(const AssetIndexParams& params) const;
    [[nodiscard]] common::RestRequest basis_request(const BasisParams& params) const;
    [[nodiscard]] common::RestRequest check_server_time_request() const;
    [[nodiscard]] common::RestRequest composite_index_symbol_information_request(
        const CompositeIndexSymbolInformationParams& params) const;
    [[nodiscard]] common::RestRequest compressed_aggregate_trades_list_request(
        const CompressedAggregateTradesListParams& params) const;
    [[nodiscard]] common::RestRequest continuous_contract_kline_candlestick_data_request(
        const ContinuousContractKlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest exchange_information_request() const;
    [[nodiscard]] common::RestRequest
    get_funding_rate_history_request(const GetFundingRateHistoryParams& params) const;
    [[nodiscard]] common::RestRequest get_funding_rate_info_request() const;
    [[nodiscard]] common::RestRequest index_price_kline_candlestick_data_request(
        const IndexPriceKlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest
    kline_candlestick_data_request(const KlineCandlestickDataParams& params) const;
    [[nodiscard]] common::RestRequest
    long_short_ratio_request(const LongShortRatioParams& params) const;
    [[nodiscard]] common::RestRequest mark_price_request(const MarkPriceParams& params) const;
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
    [[nodiscard]] common::RestRequest quarterly_contract_settlement_price_request(
        const QuarterlyContractSettlementPriceParams& params) const;
    [[nodiscard]] common::RestRequest
    query_index_price_constituents_request(const QueryIndexPriceConstituentsParams& params) const;
    [[nodiscard]] common::RestRequest query_insurance_fund_balance_snapshot_request(
        const QueryInsuranceFundBalanceSnapshotParams& params) const;
    [[nodiscard]] common::RestRequest
    recent_trades_list_request(const RecentTradesListParams& params) const;
    [[nodiscard]] common::RestRequest
    rpi_order_book_request(const RpiOrderBookParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_order_book_ticker_request(const SymbolOrderBookTickerParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_price_ticker_request(const SymbolPriceTickerParams& params) const;
    [[nodiscard]] common::RestRequest
    symbol_price_ticker_v2_request(const SymbolPriceTickerV2Params& params) const;
    [[nodiscard]] common::RestRequest
    taker_buy_sell_volume_request(const TakerBuySellVolumeParams& params) const;
    [[nodiscard]] common::RestRequest test_connectivity_request() const;
    [[nodiscard]] common::RestRequest ticker24hr_price_change_statistics_request(
        const Ticker24hrPriceChangeStatisticsParams& params) const;
    [[nodiscard]] common::RestRequest top_trader_long_short_ratio_accounts_request(
        const TopTraderLongShortRatioAccountsParams& params) const;
    [[nodiscard]] common::RestRequest top_trader_long_short_ratio_positions_request(
        const TopTraderLongShortRatioPositionsParams& params) const;
    [[nodiscard]] common::RestRequest trading_schedule_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_usds_futures::rest_api
