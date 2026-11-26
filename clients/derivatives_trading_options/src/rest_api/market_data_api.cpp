//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_options/rest_api/market_data_api.hpp>

namespace binance::derivatives_trading_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(KlineCandlestickDataIntervalEnum value) noexcept {
    switch (value) {
    case KlineCandlestickDataIntervalEnum::Interval1m:
        return "1m";
    case KlineCandlestickDataIntervalEnum::Interval3m:
        return "3m";
    case KlineCandlestickDataIntervalEnum::Interval5m:
        return "5m";
    case KlineCandlestickDataIntervalEnum::Interval15m:
        return "15m";
    case KlineCandlestickDataIntervalEnum::Interval30m:
        return "30m";
    case KlineCandlestickDataIntervalEnum::Interval1h:
        return "1h";
    case KlineCandlestickDataIntervalEnum::Interval2h:
        return "2h";
    case KlineCandlestickDataIntervalEnum::Interval4h:
        return "4h";
    case KlineCandlestickDataIntervalEnum::Interval6h:
        return "6h";
    case KlineCandlestickDataIntervalEnum::Interval8h:
        return "8h";
    case KlineCandlestickDataIntervalEnum::Interval12h:
        return "12h";
    case KlineCandlestickDataIntervalEnum::Interval1d:
        return "1d";
    case KlineCandlestickDataIntervalEnum::Interval3d:
        return "3d";
    case KlineCandlestickDataIntervalEnum::Interval1w:
        return "1w";
    case KlineCandlestickDataIntervalEnum::Interval1Month:
        return "1M";
    case KlineCandlestickDataIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlineCandlestickDataIntervalEnum
tag_invoke(boost::json::value_to_tag<KlineCandlestickDataIntervalEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1m") {
        return KlineCandlestickDataIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlineCandlestickDataIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlineCandlestickDataIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlineCandlestickDataIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlineCandlestickDataIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlineCandlestickDataIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlineCandlestickDataIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlineCandlestickDataIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlineCandlestickDataIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlineCandlestickDataIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlineCandlestickDataIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlineCandlestickDataIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlineCandlestickDataIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlineCandlestickDataIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlineCandlestickDataIntervalEnum::Interval1Month;
    }
    return KlineCandlestickDataIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlineCandlestickDataIntervalEnum value) {
    if (value == KlineCandlestickDataIntervalEnum::Unknown) {
        throw std::invalid_argument("KlineCandlestickDataIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::check_server_time_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/time";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<CheckServerTimeResponse> MarketDataApi::check_server_time() const {
    return common::send<CheckServerTimeResponse>(*client_, check_server_time_request());
}

common::RestRequest MarketDataApi::exchange_information_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/exchangeInfo";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ExchangeInformationResponse> MarketDataApi::exchange_information() const {
    return common::send<ExchangeInformationResponse>(*client_, exchange_information_request());
}

common::RestRequest MarketDataApi::historical_exercise_records_request(
    const HistoricalExerciseRecordsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/exerciseHistory";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<HistoricalExerciseRecordsResponseInner>>
MarketDataApi::historical_exercise_records(const HistoricalExerciseRecordsParams& params) const {
    return common::send<std::vector<HistoricalExerciseRecordsResponseInner>>(
        *client_, historical_exercise_records_request(params));
}

common::RestRequest MarketDataApi::index_price_request(const IndexPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/index";
    common::detail::json::set_param(req.query, "underlying", params.underlying);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<IndexPriceResponse>
MarketDataApi::index_price(const IndexPriceParams& params) const {
    return common::send<IndexPriceResponse>(*client_, index_price_request(params));
}

common::RestRequest
MarketDataApi::kline_candlestick_data_request(const KlineCandlestickDataParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/klines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<std::vector<KlineCandlestickDataItemInner>>>
MarketDataApi::kline_candlestick_data(const KlineCandlestickDataParams& params) const {
    return common::send<std::vector<std::vector<KlineCandlestickDataItemInner>>>(
        *client_, kline_candlestick_data_request(params));
}

common::RestRequest MarketDataApi::open_interest_request(const OpenInterestParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/openInterest";
    common::detail::json::set_param(req.query, "underlyingAsset", params.underlying_asset);
    common::detail::json::set_param(req.query, "expiration", params.expiration);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OpenInterestResponseInner>>
MarketDataApi::open_interest(const OpenInterestParams& params) const {
    return common::send<std::vector<OpenInterestResponseInner>>(*client_,
                                                                open_interest_request(params));
}

common::RestRequest
MarketDataApi::option_mark_price_request(const OptionMarkPriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/mark";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<OptionMarkPriceResponseInner>>
MarketDataApi::option_mark_price(const OptionMarkPriceParams& params) const {
    return common::send<std::vector<OptionMarkPriceResponseInner>>(
        *client_, option_mark_price_request(params));
}

common::RestRequest MarketDataApi::order_book_request(const OrderBookParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/depth";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<OrderBookResponse>
MarketDataApi::order_book(const OrderBookParams& params) const {
    return common::send<OrderBookResponse>(*client_, order_book_request(params));
}

common::RestRequest
MarketDataApi::recent_block_trades_list_request(const RecentBlockTradesListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/blockTrades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<RecentBlockTradesListResponseInner>>
MarketDataApi::recent_block_trades_list(const RecentBlockTradesListParams& params) const {
    return common::send<std::vector<RecentBlockTradesListResponseInner>>(
        *client_, recent_block_trades_list_request(params));
}

common::RestRequest
MarketDataApi::recent_trades_list_request(const RecentTradesListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/trades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<RecentTradesListResponseInner>>
MarketDataApi::recent_trades_list(const RecentTradesListParams& params) const {
    return common::send<std::vector<RecentTradesListResponseInner>>(
        *client_, recent_trades_list_request(params));
}

common::RestRequest MarketDataApi::test_connectivity_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/ping";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> MarketDataApi::test_connectivity() const {
    return common::send<boost::json::value>(*client_, test_connectivity_request());
}

common::RestRequest MarketDataApi::ticker24hr_price_change_statistics_request(
    const Ticker24hrPriceChangeStatisticsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/eapi/v1/ticker";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>
MarketDataApi::ticker24hr_price_change_statistics(
    const Ticker24hrPriceChangeStatisticsParams& params) const {
    return common::send<std::vector<Ticker24hrPriceChangeStatisticsResponseInner>>(
        *client_, ticker24hr_price_change_statistics_request(params));
}

} // namespace binance::derivatives_trading_options::rest_api
