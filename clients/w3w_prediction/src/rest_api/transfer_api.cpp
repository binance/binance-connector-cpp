//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/transfer_api.hpp>

namespace binance::w3w_prediction::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(ApplyMmDepositAccountTypeEnum value) noexcept {
    switch (value) {
    case ApplyMmDepositAccountTypeEnum::Spot:
        return "SPOT";
    case ApplyMmDepositAccountTypeEnum::Funding:
        return "FUNDING";
    case ApplyMmDepositAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

ApplyMmDepositAccountTypeEnum
tag_invoke(boost::json::value_to_tag<ApplyMmDepositAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return ApplyMmDepositAccountTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return ApplyMmDepositAccountTypeEnum::Funding;
    }
    return ApplyMmDepositAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ApplyMmDepositAccountTypeEnum value) {
    if (value == ApplyMmDepositAccountTypeEnum::Unknown) {
        throw std::invalid_argument("ApplyMmDepositAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(ApplyMmWithdrawWalletTypeEnum value) noexcept {
    switch (value) {
    case ApplyMmWithdrawWalletTypeEnum::WalletType0:
        return "0";
    case ApplyMmWithdrawWalletTypeEnum::WalletType1:
        return "1";
    case ApplyMmWithdrawWalletTypeEnum::Unknown:
        break;
    }
    return "";
}

ApplyMmWithdrawWalletTypeEnum
tag_invoke(boost::json::value_to_tag<ApplyMmWithdrawWalletTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "0") {
        return ApplyMmWithdrawWalletTypeEnum::WalletType0;
    }
    if (s == "1") {
        return ApplyMmWithdrawWalletTypeEnum::WalletType1;
    }
    return ApplyMmWithdrawWalletTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                ApplyMmWithdrawWalletTypeEnum value) {
    if (value == ApplyMmWithdrawWalletTypeEnum::Unknown) {
        throw std::invalid_argument("ApplyMmWithdrawWalletTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(CreateInboundTransferAccountTypeEnum value) noexcept {
    switch (value) {
    case CreateInboundTransferAccountTypeEnum::Spot:
        return "SPOT";
    case CreateInboundTransferAccountTypeEnum::Funding:
        return "FUNDING";
    case CreateInboundTransferAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

CreateInboundTransferAccountTypeEnum
tag_invoke(boost::json::value_to_tag<CreateInboundTransferAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return CreateInboundTransferAccountTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return CreateInboundTransferAccountTypeEnum::Funding;
    }
    return CreateInboundTransferAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                CreateInboundTransferAccountTypeEnum value) {
    if (value == CreateInboundTransferAccountTypeEnum::Unknown) {
        throw std::invalid_argument("CreateInboundTransferAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(CreateOutboundTransferAccountTypeEnum value) noexcept {
    switch (value) {
    case CreateOutboundTransferAccountTypeEnum::Spot:
        return "SPOT";
    case CreateOutboundTransferAccountTypeEnum::Funding:
        return "FUNDING";
    case CreateOutboundTransferAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

CreateOutboundTransferAccountTypeEnum
tag_invoke(boost::json::value_to_tag<CreateOutboundTransferAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "SPOT") {
        return CreateOutboundTransferAccountTypeEnum::Spot;
    }
    if (s == "FUNDING") {
        return CreateOutboundTransferAccountTypeEnum::Funding;
    }
    return CreateOutboundTransferAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                CreateOutboundTransferAccountTypeEnum value) {
    if (value == CreateOutboundTransferAccountTypeEnum::Unknown) {
        throw std::invalid_argument(
            "CreateOutboundTransferAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(CreateOutboundTransferSourceBizEnum value) noexcept {
    switch (value) {
    case CreateOutboundTransferSourceBizEnum::UserTransfer:
        return "USER_TRANSFER";
    case CreateOutboundTransferSourceBizEnum::PredictionBuy:
        return "PREDICTION_BUY";
    case CreateOutboundTransferSourceBizEnum::Unknown:
        break;
    }
    return "";
}

CreateOutboundTransferSourceBizEnum
tag_invoke(boost::json::value_to_tag<CreateOutboundTransferSourceBizEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USER_TRANSFER") {
        return CreateOutboundTransferSourceBizEnum::UserTransfer;
    }
    if (s == "PREDICTION_BUY") {
        return CreateOutboundTransferSourceBizEnum::PredictionBuy;
    }
    return CreateOutboundTransferSourceBizEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                CreateOutboundTransferSourceBizEnum value) {
    if (value == CreateOutboundTransferSourceBizEnum::Unknown) {
        throw std::invalid_argument("CreateOutboundTransferSourceBizEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryTransferListDirectionEnum value) noexcept {
    switch (value) {
    case QueryTransferListDirectionEnum::Inbound:
        return "INBOUND";
    case QueryTransferListDirectionEnum::Outbound:
        return "OUTBOUND";
    case QueryTransferListDirectionEnum::Unknown:
        break;
    }
    return "";
}

QueryTransferListDirectionEnum
tag_invoke(boost::json::value_to_tag<QueryTransferListDirectionEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "INBOUND") {
        return QueryTransferListDirectionEnum::Inbound;
    }
    if (s == "OUTBOUND") {
        return QueryTransferListDirectionEnum::Outbound;
    }
    return QueryTransferListDirectionEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryTransferListDirectionEnum value) {
    if (value == QueryTransferListDirectionEnum::Unknown) {
        throw std::invalid_argument("QueryTransferListDirectionEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

TransferApi::TransferApi(std::shared_ptr<common::RestClient> client) : client_(std::move(client)) {}

common::RestRequest
TransferApi::apply_mm_deposit_request(const ApplyMmDepositParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/deposit/apply";
    common::detail::json::set_param(req.query, "fromToken", params.from_token);
    common::detail::json::set_param(req.query, "fromTokenAmount", params.from_token_amount);
    common::detail::json::set_param(req.query, "toToken", params.to_token);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "chainId", params.chain_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ApplyMmDepositResponse>
TransferApi::apply_mm_deposit(const ApplyMmDepositParams& params) const {
    return common::send<ApplyMmDepositResponse>(*client_, apply_mm_deposit_request(params));
}

common::RestRequest
TransferApi::apply_mm_withdraw_request(const ApplyMmWithdrawParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/withdraw/apply";
    common::detail::json::set_param(req.query, "coin", params.coin);
    common::detail::json::set_param(req.query, "network", params.network);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "withdrawOrderId", params.withdraw_order_id);
    common::detail::json::set_param(req.query, "walletType", params.wallet_type);
    common::detail::json::set_param(req.query, "name", params.name);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<ApplyMmWithdrawResponse>
TransferApi::apply_mm_withdraw(const ApplyMmWithdrawParams& params) const {
    return common::send<ApplyMmWithdrawResponse>(*client_, apply_mm_withdraw_request(params));
}

common::RestRequest
TransferApi::create_inbound_transfer_request(const CreateInboundTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/transfer/inbound";
    common::detail::json::set_param(req.query, "walletId", params.wallet_id);
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "fromTokenAmount", params.from_token_amount);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "fromToken", params.from_token);
    common::detail::json::set_param(req.query, "toToken", params.to_token);
    common::detail::json::set_param(req.query, "chainId", params.chain_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateInboundTransferResponse>
TransferApi::create_inbound_transfer(const CreateInboundTransferParams& params) const {
    return common::send<CreateInboundTransferResponse>(*client_,
                                                       create_inbound_transfer_request(params));
}

common::RestRequest
TransferApi::create_outbound_transfer_request(const CreateOutboundTransferParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/transfer/outbound";
    common::detail::json::set_param(req.query, "walletId", params.wallet_id);
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "fromTokenAmount", params.from_token_amount);
    common::detail::json::set_param(req.query, "accountType", params.account_type);
    common::detail::json::set_param(req.query, "sourceBiz", params.source_biz);
    common::detail::json::set_param(req.query, "fromToken", params.from_token);
    common::detail::json::set_param(req.query, "toToken", params.to_token);
    common::detail::json::set_param(req.query, "chainId", params.chain_id);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<CreateOutboundTransferResponse>
TransferApi::create_outbound_transfer(const CreateOutboundTransferParams& params) const {
    return common::send<CreateOutboundTransferResponse>(*client_,
                                                        create_outbound_transfer_request(params));
}

common::RestRequest
TransferApi::query_transfer_list_request(const QueryTransferListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/transfer/list";
    common::detail::json::set_param(req.query, "walletAddress", params.wallet_address);
    common::detail::json::set_param(req.query, "startDate", params.start_date);
    common::detail::json::set_param(req.query, "endDate", params.end_date);
    common::detail::json::set_param(req.query, "tokenSymbol", params.token_symbol);
    common::detail::json::set_param(req.query, "direction", params.direction);
    common::detail::json::set_param(req.query, "offset", params.offset);
    common::detail::json::set_param(req.query, "limit", params.limit);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryTransferListResponse>
TransferApi::query_transfer_list(const QueryTransferListParams& params) const {
    return common::send<QueryTransferListResponse>(*client_, query_transfer_list_request(params));
}

common::RestRequest
TransferApi::query_transfer_status_request(const QueryTransferStatusParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/w3w/wallet/prediction/transfer/status";
    common::detail::json::set_param(req.query, "transferId", params.transfer_id);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryTransferStatusResponse>
TransferApi::query_transfer_status(const QueryTransferStatusParams& params) const {
    return common::send<QueryTransferStatusResponse>(*client_,
                                                     query_transfer_status_request(params));
}

} // namespace binance::w3w_prediction::rest_api
