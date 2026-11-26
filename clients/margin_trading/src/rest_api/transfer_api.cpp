//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/transfer_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetCrossMarginTransferHistoryTypeEnum value) noexcept {
    switch (value) {
    case GetCrossMarginTransferHistoryTypeEnum::RollIn:
        return "ROLL_IN";
    case GetCrossMarginTransferHistoryTypeEnum::RollOut:
        return "ROLL_OUT";
    case GetCrossMarginTransferHistoryTypeEnum::Unknown:
        break;
    }
    return "";
}

GetCrossMarginTransferHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetCrossMarginTransferHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "ROLL_IN") {
        return GetCrossMarginTransferHistoryTypeEnum::RollIn;
    }
    if (s == "ROLL_OUT") {
        return GetCrossMarginTransferHistoryTypeEnum::RollOut;
    }
    return GetCrossMarginTransferHistoryTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetCrossMarginTransferHistoryTypeEnum value) {
    if (value == GetCrossMarginTransferHistoryTypeEnum::Unknown) {
        throw std::invalid_argument(
            "GetCrossMarginTransferHistoryTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TransferApi::TransferApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest TransferApi::get_cross_margin_transfer_history_request(
    const GetCrossMarginTransferHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/transfer";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetCrossMarginTransferHistoryResponse>
TransferApi::get_cross_margin_transfer_history(
    const GetCrossMarginTransferHistoryParams& params) const {
    return common::send<GetCrossMarginTransferHistoryResponse>(
        *client_, get_cross_margin_transfer_history_request(params));
}

common::RestRequest TransferApi::query_max_transfer_out_amount_request(
    const QueryMaxTransferOutAmountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/maxTransferable";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMaxTransferOutAmountResponse>
TransferApi::query_max_transfer_out_amount(const QueryMaxTransferOutAmountParams& params) const {
    return common::send<QueryMaxTransferOutAmountResponse>(
        *client_, query_max_transfer_out_amount_request(params));
}

} // namespace binance::margin_trading::rest_api
