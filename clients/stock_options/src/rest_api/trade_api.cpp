//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/trade_api.hpp>

namespace binance::stock_options::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(PlaceOptionOrderSideEnum value) noexcept {
    switch (value) {
    case PlaceOptionOrderSideEnum::Buy:
        return "BUY";
    case PlaceOptionOrderSideEnum::Sell:
        return "SELL";
    case PlaceOptionOrderSideEnum::Unknown:
        break;
    }
    return "";
}

PlaceOptionOrderSideEnum tag_invoke(boost::json::value_to_tag<PlaceOptionOrderSideEnum> /*tag*/,
                                    const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return PlaceOptionOrderSideEnum::Buy;
    }
    if (s == "SELL") {
        return PlaceOptionOrderSideEnum::Sell;
    }
    return PlaceOptionOrderSideEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOptionOrderSideEnum value) {
    if (value == PlaceOptionOrderSideEnum::Unknown) {
        throw std::invalid_argument("PlaceOptionOrderSideEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOptionOrderPositionIntentEnum value) noexcept {
    switch (value) {
    case PlaceOptionOrderPositionIntentEnum::BuyToOpen:
        return "BUY_TO_OPEN";
    case PlaceOptionOrderPositionIntentEnum::SellToClose:
        return "SELL_TO_CLOSE";
    case PlaceOptionOrderPositionIntentEnum::SellToOpen:
        return "SELL_TO_OPEN";
    case PlaceOptionOrderPositionIntentEnum::BuyToClose:
        return "BUY_TO_CLOSE";
    case PlaceOptionOrderPositionIntentEnum::Unknown:
        break;
    }
    return "";
}

PlaceOptionOrderPositionIntentEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderPositionIntentEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY_TO_OPEN") {
        return PlaceOptionOrderPositionIntentEnum::BuyToOpen;
    }
    if (s == "SELL_TO_CLOSE") {
        return PlaceOptionOrderPositionIntentEnum::SellToClose;
    }
    if (s == "SELL_TO_OPEN") {
        return PlaceOptionOrderPositionIntentEnum::SellToOpen;
    }
    if (s == "BUY_TO_CLOSE") {
        return PlaceOptionOrderPositionIntentEnum::BuyToClose;
    }
    return PlaceOptionOrderPositionIntentEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOptionOrderPositionIntentEnum value) {
    if (value == PlaceOptionOrderPositionIntentEnum::Unknown) {
        throw std::invalid_argument("PlaceOptionOrderPositionIntentEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOptionOrderTimeInForceEnum value) noexcept {
    switch (value) {
    case PlaceOptionOrderTimeInForceEnum::Day:
        return "DAY";
    case PlaceOptionOrderTimeInForceEnum::Unknown:
        break;
    }
    return "";
}

PlaceOptionOrderTimeInForceEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderTimeInForceEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "DAY") {
        return PlaceOptionOrderTimeInForceEnum::Day;
    }
    return PlaceOptionOrderTimeInForceEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOptionOrderTimeInForceEnum value) {
    if (value == PlaceOptionOrderTimeInForceEnum::Unknown) {
        throw std::invalid_argument("PlaceOptionOrderTimeInForceEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(PlaceOptionOrderWalletTypeEnum value) noexcept {
    switch (value) {
    case PlaceOptionOrderWalletTypeEnum::Card:
        return "CARD";
    case PlaceOptionOrderWalletTypeEnum::Main:
        return "MAIN";
    case PlaceOptionOrderWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

PlaceOptionOrderWalletTypeEnum
tag_invoke(boost::json::value_to_tag<PlaceOptionOrderWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CARD") {
        return PlaceOptionOrderWalletTypeEnum::Card;
    }
    if (s == "MAIN") {
        return PlaceOptionOrderWalletTypeEnum::Main;
    }
    return PlaceOptionOrderWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                PlaceOptionOrderWalletTypeEnum value) {
    if (value == PlaceOptionOrderWalletTypeEnum::Unknown) {
        throw std::invalid_argument("PlaceOptionOrderWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TradeApi::TradeApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TradeApi::cancel_all_option_orders_request(const CancelAllOptionOrdersParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/option/order/cancel-all";
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelAllOptionOrdersResponse>
TradeApi::cancel_all_option_orders(const CancelAllOptionOrdersParams& params) const {
    return common::send<CancelAllOptionOrdersResponse>(*client_,
                                                       cancel_all_option_orders_request(params));
}

common::RestRequest
TradeApi::cancel_option_order_request(const CancelOptionOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/option/order/cancel";
    common::detail::json::set_param(req.query, "orderId", params.order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CancelOptionOrderResponse>
TradeApi::cancel_option_order(const CancelOptionOrderParams& params) const {
    return common::send<CancelOptionOrderResponse>(*client_, cancel_option_order_request(params));
}

common::RestRequest
TradeApi::place_option_order_request(const PlaceOptionOrderParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/option/order/place";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "side", params.side);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "price", params.price);
    common::detail::json::set_param(req.query, "quoteAsset", params.quote_asset);
    common::detail::json::set_param(req.query, "positionIntent", params.position_intent);
    common::detail::json::set_param(req.query, "timeInForce", params.time_in_force);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<PlaceOptionOrderResponse>
TradeApi::place_option_order(const PlaceOptionOrderParams& params) const {
    return common::send<PlaceOptionOrderResponse>(*client_, place_option_order_request(params));
}

common::RestRequest
TradeApi::submit_option_exercise_request(const SubmitOptionExerciseParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/equity/option/exercise/submit";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "quantity", params.quantity);
    common::detail::json::set_param(req.query, "quoteAsset", params.quote_asset);
    common::detail::json::set_param(req.query, "clientOrderId", params.client_order_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<SubmitOptionExerciseResponse>
TradeApi::submit_option_exercise(const SubmitOptionExerciseParams& params) const {
    return common::send<SubmitOptionExerciseResponse>(*client_,
                                                      submit_option_exercise_request(params));
}

} // namespace binance::stock_options::rest_api
