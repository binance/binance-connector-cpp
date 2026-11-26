//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/general_api.hpp>

namespace binance::spot::websocket_api {

std::string_view to_string(ExchangeInfoSymbolStatusEnum value) noexcept {
    switch (value) {
    case ExchangeInfoSymbolStatusEnum::Trading:
        return "TRADING";
    case ExchangeInfoSymbolStatusEnum::Halt:
        return "HALT";
    case ExchangeInfoSymbolStatusEnum::Break:
        return "BREAK";
    case ExchangeInfoSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case ExchangeInfoSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

ExchangeInfoSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<ExchangeInfoSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return ExchangeInfoSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return ExchangeInfoSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return ExchangeInfoSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return ExchangeInfoSymbolStatusEnum::CancelOnly;
    }
    return ExchangeInfoSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ExchangeInfoSymbolStatusEnum value) {
    if (value == ExchangeInfoSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("ExchangeInfoSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ExecutionRulesSymbolStatusEnum value) noexcept {
    switch (value) {
    case ExecutionRulesSymbolStatusEnum::Trading:
        return "TRADING";
    case ExecutionRulesSymbolStatusEnum::Halt:
        return "HALT";
    case ExecutionRulesSymbolStatusEnum::Break:
        return "BREAK";
    case ExecutionRulesSymbolStatusEnum::CancelOnly:
        return "CANCEL_ONLY";
    case ExecutionRulesSymbolStatusEnum::Unknown:
        break;
    }
    return "";
}

ExecutionRulesSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<ExecutionRulesSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRADING") {
        return ExecutionRulesSymbolStatusEnum::Trading;
    }
    if (s == "HALT") {
        return ExecutionRulesSymbolStatusEnum::Halt;
    }
    if (s == "BREAK") {
        return ExecutionRulesSymbolStatusEnum::Break;
    }
    if (s == "CANCEL_ONLY") {
        return ExecutionRulesSymbolStatusEnum::CancelOnly;
    }
    return ExecutionRulesSymbolStatusEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ExecutionRulesSymbolStatusEnum value) {
    if (value == ExecutionRulesSymbolStatusEnum::Unknown) {
        throw std::invalid_argument("ExecutionRulesSymbolStatusEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

GeneralApi::GeneralApi(std::shared_ptr<common::WebsocketApi> client) : client_(std::move(client)) {}

common::Params GeneralApi::exchange_info_payload(const ExchangeInfoParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "symbols", params.symbols);
    common::detail::json::set_param(p, "permissions", params.permissions);
    common::detail::json::set_param(p, "showPermissionSets", params.show_permission_sets);
    common::detail::json::set_param(p, "symbolStatus", params.symbol_status);
    return p;
}

common::WebsocketApiResponse<ExchangeInfoResponse>
GeneralApi::exchange_info(const ExchangeInfoParams& params) const {
    return common::send<ExchangeInfoResponse>(*client_, "exchangeInfo",
                                              exchange_info_payload(params),
                                              make_options(false, false, false, false));
}

common::Params GeneralApi::execution_rules_payload(const ExecutionRulesParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    common::detail::json::set_param(p, "symbol", params.symbol);
    common::detail::json::set_param(p, "symbols", params.symbols);
    common::detail::json::set_param(p, "symbolStatus", params.symbol_status);
    return p;
}

common::WebsocketApiResponse<ExecutionRulesResponseResult>
GeneralApi::execution_rules(const ExecutionRulesParams& params) const {
    return common::send<ExecutionRulesResponseResult>(*client_, "executionRules",
                                                      execution_rules_payload(params),
                                                      make_options(false, false, false, false));
}

common::Params GeneralApi::ping_payload(const PingParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<boost::json::value> GeneralApi::ping(const PingParams& params) const {
    return common::send<boost::json::value>(*client_, "ping", ping_payload(params),
                                            make_options(false, false, false, false));
}

common::Params GeneralApi::time_payload(const TimeParams& params) {
    common::Params p;
    common::detail::json::set_param(p, "id", params.id);
    return p;
}

common::WebsocketApiResponse<TimeResponseResult> GeneralApi::time(const TimeParams& params) const {
    return common::send<TimeResponseResult>(*client_, "time", time_payload(params),
                                            make_options(false, false, false, false));
}

} // namespace binance::spot::websocket_api
