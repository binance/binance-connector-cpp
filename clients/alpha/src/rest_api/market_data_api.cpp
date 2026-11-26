//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/alpha/rest_api/market_data_api.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(FullDepthLimitEnum value) noexcept {
    switch (value) {
    case FullDepthLimitEnum::Limit5:
        return "5";
    case FullDepthLimitEnum::Limit10:
        return "10";
    case FullDepthLimitEnum::Limit20:
        return "20";
    case FullDepthLimitEnum::Limit50:
        return "50";
    case FullDepthLimitEnum::Limit100:
        return "100";
    case FullDepthLimitEnum::Limit500:
        return "500";
    case FullDepthLimitEnum::Limit1000:
        return "1000";
    case FullDepthLimitEnum::Unknown:
        break;
    }
    return "";
}

FullDepthLimitEnum tag_invoke(boost::json::value_to_tag<FullDepthLimitEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "5") {
        return FullDepthLimitEnum::Limit5;
    }
    if (s == "10") {
        return FullDepthLimitEnum::Limit10;
    }
    if (s == "20") {
        return FullDepthLimitEnum::Limit20;
    }
    if (s == "50") {
        return FullDepthLimitEnum::Limit50;
    }
    if (s == "100") {
        return FullDepthLimitEnum::Limit100;
    }
    if (s == "500") {
        return FullDepthLimitEnum::Limit500;
    }
    if (s == "1000") {
        return FullDepthLimitEnum::Limit1000;
    }
    return FullDepthLimitEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                FullDepthLimitEnum value) {
    if (value == FullDepthLimitEnum::Unknown) {
        throw std::invalid_argument("FullDepthLimitEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(KlinesIntervalEnum value) noexcept {
    switch (value) {
    case KlinesIntervalEnum::Interval1s:
        return "1s";
    case KlinesIntervalEnum::Interval15s:
        return "15s";
    case KlinesIntervalEnum::Interval1m:
        return "1m";
    case KlinesIntervalEnum::Interval3m:
        return "3m";
    case KlinesIntervalEnum::Interval5m:
        return "5m";
    case KlinesIntervalEnum::Interval15m:
        return "15m";
    case KlinesIntervalEnum::Interval30m:
        return "30m";
    case KlinesIntervalEnum::Interval1h:
        return "1h";
    case KlinesIntervalEnum::Interval2h:
        return "2h";
    case KlinesIntervalEnum::Interval4h:
        return "4h";
    case KlinesIntervalEnum::Interval6h:
        return "6h";
    case KlinesIntervalEnum::Interval8h:
        return "8h";
    case KlinesIntervalEnum::Interval12h:
        return "12h";
    case KlinesIntervalEnum::Interval1d:
        return "1d";
    case KlinesIntervalEnum::Interval3d:
        return "3d";
    case KlinesIntervalEnum::Interval1w:
        return "1w";
    case KlinesIntervalEnum::Interval1Month:
        return "1M";
    case KlinesIntervalEnum::Unknown:
        break;
    }
    return "";
}

KlinesIntervalEnum tag_invoke(boost::json::value_to_tag<KlinesIntervalEnum> /*tag*/,
                              const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "1s") {
        return KlinesIntervalEnum::Interval1s;
    }
    if (s == "15s") {
        return KlinesIntervalEnum::Interval15s;
    }
    if (s == "1m") {
        return KlinesIntervalEnum::Interval1m;
    }
    if (s == "3m") {
        return KlinesIntervalEnum::Interval3m;
    }
    if (s == "5m") {
        return KlinesIntervalEnum::Interval5m;
    }
    if (s == "15m") {
        return KlinesIntervalEnum::Interval15m;
    }
    if (s == "30m") {
        return KlinesIntervalEnum::Interval30m;
    }
    if (s == "1h") {
        return KlinesIntervalEnum::Interval1h;
    }
    if (s == "2h") {
        return KlinesIntervalEnum::Interval2h;
    }
    if (s == "4h") {
        return KlinesIntervalEnum::Interval4h;
    }
    if (s == "6h") {
        return KlinesIntervalEnum::Interval6h;
    }
    if (s == "8h") {
        return KlinesIntervalEnum::Interval8h;
    }
    if (s == "12h") {
        return KlinesIntervalEnum::Interval12h;
    }
    if (s == "1d") {
        return KlinesIntervalEnum::Interval1d;
    }
    if (s == "3d") {
        return KlinesIntervalEnum::Interval3d;
    }
    if (s == "1w") {
        return KlinesIntervalEnum::Interval1w;
    }
    if (s == "1M") {
        return KlinesIntervalEnum::Interval1Month;
    }
    return KlinesIntervalEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                KlinesIntervalEnum value) {
    if (value == KlinesIntervalEnum::Unknown) {
        throw std::invalid_argument("KlinesIntervalEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
MarketDataApi::aggregated_trades_request(const AggregatedTradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/alpha-trade/agg-trades";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "fromId", params.from_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<AggregatedTradesResponse>
MarketDataApi::aggregated_trades(const AggregatedTradesParams& params) const {
    return common::send<AggregatedTradesResponse>(*client_, aggregated_trades_request(params));
}

common::RestRequest MarketDataApi::full_depth_request(const FullDepthParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/alpha-trade/fullDepth";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<FullDepthResponse>
MarketDataApi::full_depth(const FullDepthParams& params) const {
    return common::send<FullDepthResponse>(*client_, full_depth_request(params));
}

common::RestRequest MarketDataApi::get_exchange_info_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/alpha-trade/get-exchange-info";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<GetExchangeInfoResponse> MarketDataApi::get_exchange_info() const {
    return common::send<GetExchangeInfoResponse>(*client_, get_exchange_info_request());
}

common::RestRequest MarketDataApi::klines_request(const KlinesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/alpha-trade/klines";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "interval", params.interval);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<KlinesResponse> MarketDataApi::klines(const KlinesParams& params) const {
    return common::send<KlinesResponse>(*client_, klines_request(params));
}

common::RestRequest MarketDataApi::ticker_request(const TickerParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/alpha-trade/ticker";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TickerResponse> MarketDataApi::ticker(const TickerParams& params) const {
    return common::send<TickerResponse>(*client_, ticker_request(params));
}

common::RestRequest MarketDataApi::token_list_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/bapi/defi/v1/public/wallet-direct/buw/wallet/cex/alpha/all/token/list";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TokenListResponse> MarketDataApi::token_list() const {
    return common::send<TokenListResponse>(*client_, token_list_request());
}

} // namespace binance::alpha::rest_api
