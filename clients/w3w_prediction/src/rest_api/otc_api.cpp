//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/otc_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(CreateOtcBlocktradeSideEnum value) noexcept {
    switch (value) {
    case CreateOtcBlocktradeSideEnum::Buy:
        return "BUY";
    case CreateOtcBlocktradeSideEnum::Sell:
        return "SELL";
    case CreateOtcBlocktradeSideEnum::Unknown:
        break;
    }
    return "";
}

CreateOtcBlocktradeSideEnum
tag_invoke(boost::json::value_to_tag<CreateOtcBlocktradeSideEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return CreateOtcBlocktradeSideEnum::Buy;
    }
    if (s == "SELL") {
        return CreateOtcBlocktradeSideEnum::Sell;
    }
    return CreateOtcBlocktradeSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                CreateOtcBlocktradeSideEnum value) {
    if (value == CreateOtcBlocktradeSideEnum::Unknown) {
        throw std::invalid_argument("CreateOtcBlocktradeSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ListOtcBlocktradesStatusEnum value) noexcept {
    switch (value) {
    case ListOtcBlocktradesStatusEnum::Open:
        return "OPEN";
    case ListOtcBlocktradesStatusEnum::Fulfilled:
        return "FULFILLED";
    case ListOtcBlocktradesStatusEnum::Matched:
        return "MATCHED";
    case ListOtcBlocktradesStatusEnum::Cancelled:
        return "CANCELLED";
    case ListOtcBlocktradesStatusEnum::Expired:
        return "EXPIRED";
    case ListOtcBlocktradesStatusEnum::Failed:
        return "FAILED";
    case ListOtcBlocktradesStatusEnum::Unknown:
        break;
    }
    return "";
}

ListOtcBlocktradesStatusEnum
tag_invoke(boost::json::value_to_tag<ListOtcBlocktradesStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "OPEN") {
        return ListOtcBlocktradesStatusEnum::Open;
    }
    if (s == "FULFILLED") {
        return ListOtcBlocktradesStatusEnum::Fulfilled;
    }
    if (s == "MATCHED") {
        return ListOtcBlocktradesStatusEnum::Matched;
    }
    if (s == "CANCELLED") {
        return ListOtcBlocktradesStatusEnum::Cancelled;
    }
    if (s == "EXPIRED") {
        return ListOtcBlocktradesStatusEnum::Expired;
    }
    if (s == "FAILED") {
        return ListOtcBlocktradesStatusEnum::Failed;
    }
    return ListOtcBlocktradesStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ListOtcBlocktradesStatusEnum value) {
    if (value == ListOtcBlocktradesStatusEnum::Unknown) {
        throw std::invalid_argument("ListOtcBlocktradesStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

OtcApi::OtcApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
OtcApi::create_otc_blocktrade_request(const CreateOtcBlocktradeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/create";
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "makerAmount", params.maker_amount);
    common::detail::json::set_param(req.query, "takerAmount", params.taker_amount);
    common::detail::json::set_param(req.query, "pricePerShare", params.price_per_share);
    common::detail::json::set_param(req.query, "expiration", params.expiration);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateOtcBlocktradeResponse>
OtcApi::create_otc_blocktrade(const CreateOtcBlocktradeParams& params) const {
    return common::send<CreateOtcBlocktradeResponse>(*client_,
                                                     create_otc_blocktrade_request(params));
}

common::RestRequest
OtcApi::fulfil_otc_blocktrade_request(const FulfilOtcBlocktradeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/fulfil";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "secretToken", params.secret_token);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<FulfilOtcBlocktradeResponse>
OtcApi::fulfil_otc_blocktrade(const FulfilOtcBlocktradeParams& params) const {
    return common::send<FulfilOtcBlocktradeResponse>(*client_,
                                                     fulfil_otc_blocktrade_request(params));
}

common::RestRequest
OtcApi::get_otc_blocktrade_detail_request(const GetOtcBlocktradeDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/detail";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOtcBlocktradeDetailResponse>
OtcApi::get_otc_blocktrade_detail(const GetOtcBlocktradeDetailParams& params) const {
    return common::send<GetOtcBlocktradeDetailResponse>(*client_,
                                                        get_otc_blocktrade_detail_request(params));
}

common::RestRequest
OtcApi::get_otc_blocktrade_events_request(const GetOtcBlocktradeEventsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/events";
    common::detail::json::set_param(req.query, "first", params.first);
    common::detail::json::set_param(req.query, "after", params.after);
    common::detail::json::set_param(req.query, "eventTypes", params.event_types);
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOtcBlocktradeEventsResponse>
OtcApi::get_otc_blocktrade_events(const GetOtcBlocktradeEventsParams& params) const {
    return common::send<GetOtcBlocktradeEventsResponse>(*client_,
                                                        get_otc_blocktrade_events_request(params));
}

common::RestRequest
OtcApi::get_otc_reserved_balances_request(const GetOtcReservedBalancesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/reserved-balances";
    common::detail::json::set_param(req.query, "assets", params.assets);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetOtcReservedBalancesResponse>
OtcApi::get_otc_reserved_balances(const GetOtcReservedBalancesParams& params) const {
    return common::send<GetOtcReservedBalancesResponse>(*client_,
                                                        get_otc_reserved_balances_request(params));
}

common::RestRequest
OtcApi::list_otc_blocktrades_request(const ListOtcBlocktradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/list";
    common::detail::json::set_param(req.query, "first", params.first);
    common::detail::json::set_param(req.query, "after", params.after);
    common::detail::json::set_param(req.query, "status", params.status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ListOtcBlocktradesResponse>
OtcApi::list_otc_blocktrades(const ListOtcBlocktradesParams& params) const {
    return common::send<ListOtcBlocktradesResponse>(*client_, list_otc_blocktrades_request(params));
}

common::RestRequest
OtcApi::preview_otc_blocktrade_request(const PreviewOtcBlocktradeParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/preview";
    common::detail::json::set_param(req.query, "secretToken", params.secret_token);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PreviewOtcBlocktradeResponse>
OtcApi::preview_otc_blocktrade(const PreviewOtcBlocktradeParams& params) const {
    return common::send<PreviewOtcBlocktradeResponse>(*client_,
                                                      preview_otc_blocktrade_request(params));
}

common::RestRequest
OtcApi::remove_otc_blocktrades_request(const RemoveOtcBlocktradesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/otc/blocktrade/remove";
    common::detail::json::set_param(req.query, "orderIds", params.order_ids);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<RemoveOtcBlocktradesResponse>
OtcApi::remove_otc_blocktrades(const RemoveOtcBlocktradesParams& params) const {
    return common::send<RemoveOtcBlocktradesResponse>(*client_,
                                                      remove_otc_blocktrades_request(params));
}

} // namespace binance::w3w_prediction::rest_api
