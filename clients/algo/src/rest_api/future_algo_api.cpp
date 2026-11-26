//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/algo/rest_api/future_algo_api.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(QueryHistoricalAlgoOrdersFutureAlgoSideEnum value) noexcept {
    switch (value) {
    case QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Buy:
        return "BUY";
    case QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Sell:
        return "SELL";
    case QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Unknown:
        break;
    }
    return "";
}

QueryHistoricalAlgoOrdersFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Buy;
    }
    if (s == "SELL") {
        return QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Sell;
    }
    return QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryHistoricalAlgoOrdersFutureAlgoSideEnum value) {
    if (value == QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Unknown) {
        throw std::invalid_argument(
            "QueryHistoricalAlgoOrdersFutureAlgoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TimeWeightedAveragePriceFutureAlgoSideEnum value) noexcept {
    switch (value) {
    case TimeWeightedAveragePriceFutureAlgoSideEnum::Buy:
        return "BUY";
    case TimeWeightedAveragePriceFutureAlgoSideEnum::Sell:
        return "SELL";
    case TimeWeightedAveragePriceFutureAlgoSideEnum::Unknown:
        break;
    }
    return "";
}

TimeWeightedAveragePriceFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return TimeWeightedAveragePriceFutureAlgoSideEnum::Buy;
    }
    if (s == "SELL") {
        return TimeWeightedAveragePriceFutureAlgoSideEnum::Sell;
    }
    return TimeWeightedAveragePriceFutureAlgoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TimeWeightedAveragePriceFutureAlgoSideEnum value) {
    if (value == TimeWeightedAveragePriceFutureAlgoSideEnum::Unknown) {
        throw std::invalid_argument(
            "TimeWeightedAveragePriceFutureAlgoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TimeWeightedAveragePriceFutureAlgoPositionSideEnum value) noexcept {
    switch (value) {
    case TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Both:
        return "BOTH";
    case TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Long:
        return "LONG";
    case TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Short:
        return "SHORT";
    case TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Unknown:
        break;
    }
    return "";
}

TimeWeightedAveragePriceFutureAlgoPositionSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceFutureAlgoPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Short;
    }
    return TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TimeWeightedAveragePriceFutureAlgoPositionSideEnum value) {
    if (value == TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Unknown) {
        throw std::invalid_argument(
            "TimeWeightedAveragePriceFutureAlgoPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(VolumeParticipationFutureAlgoSideEnum value) noexcept {
    switch (value) {
    case VolumeParticipationFutureAlgoSideEnum::Buy:
        return "BUY";
    case VolumeParticipationFutureAlgoSideEnum::Sell:
        return "SELL";
    case VolumeParticipationFutureAlgoSideEnum::Unknown:
        break;
    }
    return "";
}

VolumeParticipationFutureAlgoSideEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return VolumeParticipationFutureAlgoSideEnum::Buy;
    }
    if (s == "SELL") {
        return VolumeParticipationFutureAlgoSideEnum::Sell;
    }
    return VolumeParticipationFutureAlgoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                VolumeParticipationFutureAlgoSideEnum value) {
    if (value == VolumeParticipationFutureAlgoSideEnum::Unknown) {
        throw std::invalid_argument(
            "VolumeParticipationFutureAlgoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(VolumeParticipationFutureAlgoUrgencyEnum value) noexcept {
    switch (value) {
    case VolumeParticipationFutureAlgoUrgencyEnum::Low:
        return "LOW";
    case VolumeParticipationFutureAlgoUrgencyEnum::Medium:
        return "MEDIUM";
    case VolumeParticipationFutureAlgoUrgencyEnum::High:
        return "HIGH";
    case VolumeParticipationFutureAlgoUrgencyEnum::Unknown:
        break;
    }
    return "";
}

VolumeParticipationFutureAlgoUrgencyEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoUrgencyEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LOW") {
        return VolumeParticipationFutureAlgoUrgencyEnum::Low;
    }
    if (s == "MEDIUM") {
        return VolumeParticipationFutureAlgoUrgencyEnum::Medium;
    }
    if (s == "HIGH") {
        return VolumeParticipationFutureAlgoUrgencyEnum::High;
    }
    return VolumeParticipationFutureAlgoUrgencyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                VolumeParticipationFutureAlgoUrgencyEnum value) {
    if (value == VolumeParticipationFutureAlgoUrgencyEnum::Unknown) {
        throw std::invalid_argument(
            "VolumeParticipationFutureAlgoUrgencyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(VolumeParticipationFutureAlgoPositionSideEnum value) noexcept {
    switch (value) {
    case VolumeParticipationFutureAlgoPositionSideEnum::Both:
        return "BOTH";
    case VolumeParticipationFutureAlgoPositionSideEnum::Long:
        return "LONG";
    case VolumeParticipationFutureAlgoPositionSideEnum::Short:
        return "SHORT";
    case VolumeParticipationFutureAlgoPositionSideEnum::Unknown:
        break;
    }
    return "";
}

VolumeParticipationFutureAlgoPositionSideEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationFutureAlgoPositionSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BOTH") {
        return VolumeParticipationFutureAlgoPositionSideEnum::Both;
    }
    if (s == "LONG") {
        return VolumeParticipationFutureAlgoPositionSideEnum::Long;
    }
    if (s == "SHORT") {
        return VolumeParticipationFutureAlgoPositionSideEnum::Short;
    }
    return VolumeParticipationFutureAlgoPositionSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                VolumeParticipationFutureAlgoPositionSideEnum value) {
    if (value == VolumeParticipationFutureAlgoPositionSideEnum::Unknown) {
        throw std::invalid_argument(
            "VolumeParticipationFutureAlgoPositionSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

FutureAlgoApi::FutureAlgoApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest FutureAlgoApi::cancel_algo_order_future_algo_request(
    const CancelAlgoOrderFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/algo/futures/order";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAlgoOrderFutureAlgoResponse>
FutureAlgoApi::cancel_algo_order_future_algo(const CancelAlgoOrderFutureAlgoParams& params) const {
    return common::send<CancelAlgoOrderFutureAlgoResponse>(
        *client_, cancel_algo_order_future_algo_request(params));
}

common::RestRequest FutureAlgoApi::query_current_algo_open_orders_future_algo_request(
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/futures/openOrders";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentAlgoOpenOrdersFutureAlgoResponse>
FutureAlgoApi::query_current_algo_open_orders_future_algo(
    const QueryCurrentAlgoOpenOrdersFutureAlgoParams& params) const {
    return common::send<QueryCurrentAlgoOpenOrdersFutureAlgoResponse>(
        *client_, query_current_algo_open_orders_future_algo_request(params));
}

common::RestRequest FutureAlgoApi::query_historical_algo_orders_future_algo_request(
    const QueryHistoricalAlgoOrdersFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/futures/historicalOrders";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryHistoricalAlgoOrdersFutureAlgoResponse>
FutureAlgoApi::query_historical_algo_orders_future_algo(
    const QueryHistoricalAlgoOrdersFutureAlgoParams& params) const {
    return common::send<QueryHistoricalAlgoOrdersFutureAlgoResponse>(
        *client_, query_historical_algo_orders_future_algo_request(params));
}

common::RestRequest FutureAlgoApi::query_sub_orders_future_algo_request(
    const QuerySubOrdersFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/futures/subOrders";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubOrdersFutureAlgoResponse>
FutureAlgoApi::query_sub_orders_future_algo(const QuerySubOrdersFutureAlgoParams& params) const {
    return common::send<QuerySubOrdersFutureAlgoResponse>(
        *client_, query_sub_orders_future_algo_request(params));
}

common::RestRequest FutureAlgoApi::time_weighted_average_price_future_algo_request(
    const TimeWeightedAveragePriceFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/algo/futures/newOrderTwap";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "duration", params.duration);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "limitPrice", params.limit_price);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TimeWeightedAveragePriceFutureAlgoResponse>
FutureAlgoApi::time_weighted_average_price_future_algo(
    const TimeWeightedAveragePriceFutureAlgoParams& params) const {
    return common::send<TimeWeightedAveragePriceFutureAlgoResponse>(
        *client_, time_weighted_average_price_future_algo_request(params));
}

common::RestRequest FutureAlgoApi::volume_participation_future_algo_request(
    const VolumeParticipationFutureAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/algo/futures/newOrderVp";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "urgency", params.urgency);
    common::detail::json::set_param(req.query, "positionSide", params.position_side);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "reduceOnly", params.reduce_only);
    common::detail::json::set_param(req.query, "limitPrice", params.limit_price);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VolumeParticipationFutureAlgoResponse>
FutureAlgoApi::volume_participation_future_algo(
    const VolumeParticipationFutureAlgoParams& params) const {
    return common::send<VolumeParticipationFutureAlgoResponse>(
        *client_, volume_participation_future_algo_request(params));
}

} // namespace binance::algo::rest_api
