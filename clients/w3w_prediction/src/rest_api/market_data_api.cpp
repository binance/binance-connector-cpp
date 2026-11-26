//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/market_data_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(ListPredictionMarketsSortByEnum value) noexcept {
    switch (value) {
    case ListPredictionMarketsSortByEnum::Recommended:
        return "RECOMMENDED";
    case ListPredictionMarketsSortByEnum::Volume:
        return "VOLUME";
    case ListPredictionMarketsSortByEnum::Participants:
        return "PARTICIPANTS";
    case ListPredictionMarketsSortByEnum::CreatedTime:
        return "CREATED_TIME";
    case ListPredictionMarketsSortByEnum::EndDate:
        return "END_DATE";
    case ListPredictionMarketsSortByEnum::Unknown:
        break;
    }
    return "";
}

ListPredictionMarketsSortByEnum
tag_invoke(boost::json::value_to_tag<ListPredictionMarketsSortByEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "RECOMMENDED") {
        return ListPredictionMarketsSortByEnum::Recommended;
    }
    if (s == "VOLUME") {
        return ListPredictionMarketsSortByEnum::Volume;
    }
    if (s == "PARTICIPANTS") {
        return ListPredictionMarketsSortByEnum::Participants;
    }
    if (s == "CREATED_TIME") {
        return ListPredictionMarketsSortByEnum::CreatedTime;
    }
    if (s == "END_DATE") {
        return ListPredictionMarketsSortByEnum::EndDate;
    }
    return ListPredictionMarketsSortByEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ListPredictionMarketsSortByEnum value) {
    if (value == ListPredictionMarketsSortByEnum::Unknown) {
        throw std::invalid_argument("ListPredictionMarketsSortByEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ListPredictionMarketsOrderByEnum value) noexcept {
    switch (value) {
    case ListPredictionMarketsOrderByEnum::Asc:
        return "ASC";
    case ListPredictionMarketsOrderByEnum::Desc:
        return "DESC";
    case ListPredictionMarketsOrderByEnum::Unknown:
        break;
    }
    return "";
}

ListPredictionMarketsOrderByEnum
tag_invoke(boost::json::value_to_tag<ListPredictionMarketsOrderByEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ASC") {
        return ListPredictionMarketsOrderByEnum::Asc;
    }
    if (s == "DESC") {
        return ListPredictionMarketsOrderByEnum::Desc;
    }
    return ListPredictionMarketsOrderByEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ListPredictionMarketsOrderByEnum value) {
    if (value == ListPredictionMarketsOrderByEnum::Unknown) {
        throw std::invalid_argument("ListPredictionMarketsOrderByEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest
MarketDataApi::get_market_detail_request(const GetMarketDetailParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/market/detail";
    common::detail::json::set_param(req.query, "marketTopicId", params.market_topic_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetMarketDetailResponse>
MarketDataApi::get_market_detail(const GetMarketDetailParams& params) const {
    return common::send<GetMarketDetailResponse>(*client_, get_market_detail_request(params));
}

common::RestRequest MarketDataApi::list_prediction_categories_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/category/list";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ListPredictionCategoriesResponse>
MarketDataApi::list_prediction_categories() const {
    return common::send<ListPredictionCategoriesResponse>(*client_,
                                                          list_prediction_categories_request());
}

common::RestRequest
MarketDataApi::list_prediction_markets_request(const ListPredictionMarketsParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/market/list";
    common::detail::json::set_param(req.query, "l1Category", params.l1_category);
    common::detail::json::set_param(req.query, "l2Category", params.l2_category);
    common::detail::json::set_param(req.query, "sortBy", params.sort_by);
    common::detail::json::set_param(req.query, "orderBy", params.order_by);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ListPredictionMarketsResponse>
MarketDataApi::list_prediction_markets(const ListPredictionMarketsParams& params) const {
    return common::send<ListPredictionMarketsResponse>(*client_,
                                                       list_prediction_markets_request(params));
}

common::RestRequest MarketDataApi::market_search_request(const MarketSearchParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/market/search";
    common::detail::json::set_param(req.query, "query", params.query);
    common::detail::json::set_param(req.query, "topK", params.top_k);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<MarketSearchResponseInner>>
MarketDataApi::market_search(const MarketSearchParams& params) const {
    return common::send<std::vector<MarketSearchResponseInner>>(*client_,
                                                                market_search_request(params));
}

common::RestRequest
MarketDataApi::query_last_trade_price_request(const QueryLastTradePriceParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/order-book/last-trade-price";
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryLastTradePriceResponse>
MarketDataApi::query_last_trade_price(const QueryLastTradePriceParams& params) const {
    return common::send<QueryLastTradePriceResponse>(*client_,
                                                     query_last_trade_price_request(params));
}

common::RestRequest
MarketDataApi::query_order_book_request(const QueryOrderBookParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/order-book";
    common::detail::json::set_param(req.query, "vendor", params.vendor);
    common::detail::json::set_param(req.query, "marketId", params.market_id);
    common::detail::json::set_param(req.query, "tokenId", params.token_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryOrderBookResponse>
MarketDataApi::query_order_book(const QueryOrderBookParams& params) const {
    return common::send<QueryOrderBookResponse>(*client_, query_order_book_request(params));
}

} // namespace binance::w3w_prediction::rest_api
