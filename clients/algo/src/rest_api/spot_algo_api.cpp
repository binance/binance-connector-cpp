//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/algo/rest_api/spot_algo_api.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::algo::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(QueryHistoricalAlgoOrdersSpotAlgoSideEnum value) noexcept {
    switch (value) {
    case QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Buy:
        return "BUY";
    case QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Sell:
        return "SELL";
    case QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Unknown:
        break;
    }
    return "";
}

QueryHistoricalAlgoOrdersSpotAlgoSideEnum
tag_invoke(boost::json::value_to_tag<QueryHistoricalAlgoOrdersSpotAlgoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Buy;
    }
    if (s == "SELL") {
        return QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Sell;
    }
    return QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryHistoricalAlgoOrdersSpotAlgoSideEnum value) {
    if (value == QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Unknown) {
        throw std::invalid_argument(
            "QueryHistoricalAlgoOrdersSpotAlgoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(TimeWeightedAveragePriceSpotAlgoSideEnum value) noexcept {
    switch (value) {
    case TimeWeightedAveragePriceSpotAlgoSideEnum::Buy:
        return "BUY";
    case TimeWeightedAveragePriceSpotAlgoSideEnum::Sell:
        return "SELL";
    case TimeWeightedAveragePriceSpotAlgoSideEnum::Unknown:
        break;
    }
    return "";
}

TimeWeightedAveragePriceSpotAlgoSideEnum
tag_invoke(boost::json::value_to_tag<TimeWeightedAveragePriceSpotAlgoSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return TimeWeightedAveragePriceSpotAlgoSideEnum::Buy;
    }
    if (s == "SELL") {
        return TimeWeightedAveragePriceSpotAlgoSideEnum::Sell;
    }
    return TimeWeightedAveragePriceSpotAlgoSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                TimeWeightedAveragePriceSpotAlgoSideEnum value) {
    if (value == TimeWeightedAveragePriceSpotAlgoSideEnum::Unknown) {
        throw std::invalid_argument(
            "TimeWeightedAveragePriceSpotAlgoSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(VolumeParticipationSideEnum value) noexcept {
    switch (value) {
    case VolumeParticipationSideEnum::Buy:
        return "BUY";
    case VolumeParticipationSideEnum::Sell:
        return "SELL";
    case VolumeParticipationSideEnum::Unknown:
        break;
    }
    return "";
}

VolumeParticipationSideEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return VolumeParticipationSideEnum::Buy;
    }
    if (s == "SELL") {
        return VolumeParticipationSideEnum::Sell;
    }
    return VolumeParticipationSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                VolumeParticipationSideEnum value) {
    if (value == VolumeParticipationSideEnum::Unknown) {
        throw std::invalid_argument("VolumeParticipationSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(VolumeParticipationUrgencyEnum value) noexcept {
    switch (value) {
    case VolumeParticipationUrgencyEnum::Low:
        return "LOW";
    case VolumeParticipationUrgencyEnum::Medium:
        return "MEDIUM";
    case VolumeParticipationUrgencyEnum::High:
        return "HIGH";
    case VolumeParticipationUrgencyEnum::Unknown:
        break;
    }
    return "";
}

VolumeParticipationUrgencyEnum
tag_invoke(boost::json::value_to_tag<VolumeParticipationUrgencyEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "LOW") {
        return VolumeParticipationUrgencyEnum::Low;
    }
    if (s == "MEDIUM") {
        return VolumeParticipationUrgencyEnum::Medium;
    }
    if (s == "HIGH") {
        return VolumeParticipationUrgencyEnum::High;
    }
    return VolumeParticipationUrgencyEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                VolumeParticipationUrgencyEnum value) {
    if (value == VolumeParticipationUrgencyEnum::Unknown) {
        throw std::invalid_argument("VolumeParticipationUrgencyEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

SpotAlgoApi::SpotAlgoApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest SpotAlgoApi::cancel_algo_order_spot_algo_request(
    const CancelAlgoOrderSpotAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Delete;
    req.endpoint = "/sapi/v1/algo/spot/order";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAlgoOrderSpotAlgoResponse>
SpotAlgoApi::cancel_algo_order_spot_algo(const CancelAlgoOrderSpotAlgoParams& params) const {
    return common::send<CancelAlgoOrderSpotAlgoResponse>(
        *client_, cancel_algo_order_spot_algo_request(params));
}

common::RestRequest SpotAlgoApi::query_current_algo_open_orders_spot_algo_request(
    const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/spot/openOrders";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryCurrentAlgoOpenOrdersSpotAlgoResponse>
SpotAlgoApi::query_current_algo_open_orders_spot_algo(
    const QueryCurrentAlgoOpenOrdersSpotAlgoParams& params) const {
    return common::send<QueryCurrentAlgoOpenOrdersSpotAlgoResponse>(
        *client_, query_current_algo_open_orders_spot_algo_request(params));
}

common::RestRequest SpotAlgoApi::query_historical_algo_orders_spot_algo_request(
    const QueryHistoricalAlgoOrdersSpotAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/spot/historicalOrders";
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

common::RestApiResponse<QueryHistoricalAlgoOrdersSpotAlgoResponse>
SpotAlgoApi::query_historical_algo_orders_spot_algo(
    const QueryHistoricalAlgoOrdersSpotAlgoParams& params) const {
    return common::send<QueryHistoricalAlgoOrdersSpotAlgoResponse>(
        *client_, query_historical_algo_orders_spot_algo_request(params));
}

common::RestRequest
SpotAlgoApi::query_sub_orders_spot_algo_request(const QuerySubOrdersSpotAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/algo/spot/subOrders";
    common::detail::json::set_param(req.query, "algoId", params.algo_id);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QuerySubOrdersSpotAlgoResponse>
SpotAlgoApi::query_sub_orders_spot_algo(const QuerySubOrdersSpotAlgoParams& params) const {
    return common::send<QuerySubOrdersSpotAlgoResponse>(*client_,
                                                        query_sub_orders_spot_algo_request(params));
}

common::RestRequest SpotAlgoApi::time_weighted_average_price_spot_algo_request(
    const TimeWeightedAveragePriceSpotAlgoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/algo/spot/newOrderTwap";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "duration", params.duration);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "limitPrice", params.limit_price);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<TimeWeightedAveragePriceSpotAlgoResponse>
SpotAlgoApi::time_weighted_average_price_spot_algo(
    const TimeWeightedAveragePriceSpotAlgoParams& params) const {
    return common::send<TimeWeightedAveragePriceSpotAlgoResponse>(
        *client_, time_weighted_average_price_spot_algo_request(params));
}

common::RestRequest
SpotAlgoApi::volume_participation_request(const VolumeParticipationParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/algo/spot/newOrderVp";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "urgency", params.urgency);
    common::detail::json::set_param(req.query, "clientAlgoId", params.client_algo_id);
    common::detail::json::set_param(req.query, "vpTimeLimit", params.vp_time_limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<VolumeParticipationResponse>
SpotAlgoApi::volume_participation(const VolumeParticipationParams& params) const {
    return common::send<VolumeParticipationResponse>(*client_,
                                                     volume_participation_request(params));
}

} // namespace binance::algo::rest_api
