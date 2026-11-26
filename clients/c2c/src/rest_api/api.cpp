//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/c2c/rest_api/api.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::c2c::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetC2CTradeHistoryTradeTypeEnum value) noexcept {
    switch (value) {
    case GetC2CTradeHistoryTradeTypeEnum::Buy:
        return "BUY";
    case GetC2CTradeHistoryTradeTypeEnum::Sell:
        return "SELL";
    case GetC2CTradeHistoryTradeTypeEnum::Unknown:
        break;
    }
    return "";
}

GetC2CTradeHistoryTradeTypeEnum
tag_invoke(boost::json::value_to_tag<GetC2CTradeHistoryTradeTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BUY") {
        return GetC2CTradeHistoryTradeTypeEnum::Buy;
    }
    if (s == "SELL") {
        return GetC2CTradeHistoryTradeTypeEnum::Sell;
    }
    return GetC2CTradeHistoryTradeTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetC2CTradeHistoryTradeTypeEnum value) {
    if (value == GetC2CTradeHistoryTradeTypeEnum::Unknown) {
        throw std::invalid_argument("GetC2CTradeHistoryTradeTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

Api::Api(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
Api::get_c2c_trade_history_request(const GetC2CTradeHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/c2c/orderMatch/listUserOrderHistory";
    common::detail::json::set_param(req.query, "tradeType", params.trade_type);
    common::detail::json::set_param(req.query, "startTimestamp", params.start_timestamp);
    common::detail::json::set_param(req.query, "endTimestamp", params.end_timestamp);
    common::detail::json::set_param(req.query, "page", params.page);
    common::detail::json::set_param(req.query, "rows", params.rows);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<GetC2CTradeHistoryResponse>
Api::get_c2c_trade_history(const GetC2CTradeHistoryParams& params) const {
    return common::send<GetC2CTradeHistoryResponse>(*client_,
                                                    get_c2c_trade_history_request(params));
}

} // namespace binance::c2c::rest_api
