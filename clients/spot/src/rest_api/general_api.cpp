//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/spot/rest_api/general_api.hpp>

namespace binance::spot::rest_api {

namespace {
constexpr bool kHasTimeUnit = true;
} // namespace

std::string_view to_string(ExchangeInfoPermissionsEnum value) noexcept {
    switch (value) {
    case ExchangeInfoPermissionsEnum::Spot:
        return "SPOT";
    case ExchangeInfoPermissionsEnum::Margin:
        return "MARGIN";
    case ExchangeInfoPermissionsEnum::Leveraged:
        return "LEVERAGED";
    case ExchangeInfoPermissionsEnum::TrdGrp002:
        return "TRD_GRP_002";
    case ExchangeInfoPermissionsEnum::TrdGrp003:
        return "TRD_GRP_003";
    case ExchangeInfoPermissionsEnum::TrdGrp004:
        return "TRD_GRP_004";
    case ExchangeInfoPermissionsEnum::TrdGrp005:
        return "TRD_GRP_005";
    case ExchangeInfoPermissionsEnum::TrdGrp006:
        return "TRD_GRP_006";
    case ExchangeInfoPermissionsEnum::TrdGrp007:
        return "TRD_GRP_007";
    case ExchangeInfoPermissionsEnum::TrdGrp008:
        return "TRD_GRP_008";
    case ExchangeInfoPermissionsEnum::TrdGrp009:
        return "TRD_GRP_009";
    case ExchangeInfoPermissionsEnum::TrdGrp010:
        return "TRD_GRP_010";
    case ExchangeInfoPermissionsEnum::TrdGrp011:
        return "TRD_GRP_011";
    case ExchangeInfoPermissionsEnum::TrdGrp012:
        return "TRD_GRP_012";
    case ExchangeInfoPermissionsEnum::TrdGrp013:
        return "TRD_GRP_013";
    case ExchangeInfoPermissionsEnum::TrdGrp014:
        return "TRD_GRP_014";
    case ExchangeInfoPermissionsEnum::TrdGrp015:
        return "TRD_GRP_015";
    case ExchangeInfoPermissionsEnum::TrdGrp016:
        return "TRD_GRP_016";
    case ExchangeInfoPermissionsEnum::TrdGrp017:
        return "TRD_GRP_017";
    case ExchangeInfoPermissionsEnum::TrdGrp018:
        return "TRD_GRP_018";
    case ExchangeInfoPermissionsEnum::TrdGrp019:
        return "TRD_GRP_019";
    case ExchangeInfoPermissionsEnum::TrdGrp020:
        return "TRD_GRP_020";
    case ExchangeInfoPermissionsEnum::TrdGrp021:
        return "TRD_GRP_021";
    case ExchangeInfoPermissionsEnum::TrdGrp022:
        return "TRD_GRP_022";
    case ExchangeInfoPermissionsEnum::TrdGrp023:
        return "TRD_GRP_023";
    case ExchangeInfoPermissionsEnum::TrdGrp024:
        return "TRD_GRP_024";
    case ExchangeInfoPermissionsEnum::TrdGrp025:
        return "TRD_GRP_025";
    case ExchangeInfoPermissionsEnum::Unknown:
        break;
    }
    return "";
}

ExchangeInfoPermissionsEnum
tag_invoke(boost::json::value_to_tag<ExchangeInfoPermissionsEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return ExchangeInfoPermissionsEnum::Spot;
    }
    if (s == "MARGIN") {
        return ExchangeInfoPermissionsEnum::Margin;
    }
    if (s == "LEVERAGED") {
        return ExchangeInfoPermissionsEnum::Leveraged;
    }
    if (s == "TRD_GRP_002") {
        return ExchangeInfoPermissionsEnum::TrdGrp002;
    }
    if (s == "TRD_GRP_003") {
        return ExchangeInfoPermissionsEnum::TrdGrp003;
    }
    if (s == "TRD_GRP_004") {
        return ExchangeInfoPermissionsEnum::TrdGrp004;
    }
    if (s == "TRD_GRP_005") {
        return ExchangeInfoPermissionsEnum::TrdGrp005;
    }
    if (s == "TRD_GRP_006") {
        return ExchangeInfoPermissionsEnum::TrdGrp006;
    }
    if (s == "TRD_GRP_007") {
        return ExchangeInfoPermissionsEnum::TrdGrp007;
    }
    if (s == "TRD_GRP_008") {
        return ExchangeInfoPermissionsEnum::TrdGrp008;
    }
    if (s == "TRD_GRP_009") {
        return ExchangeInfoPermissionsEnum::TrdGrp009;
    }
    if (s == "TRD_GRP_010") {
        return ExchangeInfoPermissionsEnum::TrdGrp010;
    }
    if (s == "TRD_GRP_011") {
        return ExchangeInfoPermissionsEnum::TrdGrp011;
    }
    if (s == "TRD_GRP_012") {
        return ExchangeInfoPermissionsEnum::TrdGrp012;
    }
    if (s == "TRD_GRP_013") {
        return ExchangeInfoPermissionsEnum::TrdGrp013;
    }
    if (s == "TRD_GRP_014") {
        return ExchangeInfoPermissionsEnum::TrdGrp014;
    }
    if (s == "TRD_GRP_015") {
        return ExchangeInfoPermissionsEnum::TrdGrp015;
    }
    if (s == "TRD_GRP_016") {
        return ExchangeInfoPermissionsEnum::TrdGrp016;
    }
    if (s == "TRD_GRP_017") {
        return ExchangeInfoPermissionsEnum::TrdGrp017;
    }
    if (s == "TRD_GRP_018") {
        return ExchangeInfoPermissionsEnum::TrdGrp018;
    }
    if (s == "TRD_GRP_019") {
        return ExchangeInfoPermissionsEnum::TrdGrp019;
    }
    if (s == "TRD_GRP_020") {
        return ExchangeInfoPermissionsEnum::TrdGrp020;
    }
    if (s == "TRD_GRP_021") {
        return ExchangeInfoPermissionsEnum::TrdGrp021;
    }
    if (s == "TRD_GRP_022") {
        return ExchangeInfoPermissionsEnum::TrdGrp022;
    }
    if (s == "TRD_GRP_023") {
        return ExchangeInfoPermissionsEnum::TrdGrp023;
    }
    if (s == "TRD_GRP_024") {
        return ExchangeInfoPermissionsEnum::TrdGrp024;
    }
    if (s == "TRD_GRP_025") {
        return ExchangeInfoPermissionsEnum::TrdGrp025;
    }
    return ExchangeInfoPermissionsEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ExchangeInfoPermissionsEnum value) {
    if (value == ExchangeInfoPermissionsEnum::Unknown) {
        throw std::invalid_argument("ExchangeInfoPermissionsEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

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

GeneralApi::GeneralApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest GeneralApi::exchange_info_request(const ExchangeInfoParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/exchangeInfo";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "permissions", params.permissions);
    common::detail::json::set_param(req.query, "showPermissionSets", params.show_permission_sets);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ExchangeInfoResponse>
GeneralApi::exchange_info(const ExchangeInfoParams& params) const {
    return common::send<ExchangeInfoResponse>(*client_, exchange_info_request(params));
}

common::RestRequest GeneralApi::execution_rules_request(const ExecutionRulesParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/executionRules";
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "symbols", params.symbols);
    common::detail::json::set_param(req.query, "symbolStatus", params.symbol_status);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<ExecutionRulesResponse>
GeneralApi::execution_rules(const ExecutionRulesParams& params) const {
    return common::send<ExecutionRulesResponse>(*client_, execution_rules_request(params));
}

common::RestRequest GeneralApi::ping_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/ping";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<boost::json::value> GeneralApi::ping() const {
    return common::send<boost::json::value>(*client_, ping_request());
}

common::RestRequest GeneralApi::time_request() const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/api/v3/time";
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<TimeResponse> GeneralApi::time() const {
    return common::send<TimeResponse>(*client_, time_request());
}

} // namespace binance::spot::rest_api
