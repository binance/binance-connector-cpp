//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/borrow_repay_api.hpp>

namespace binance::margin_trading::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetFutureHourlyInterestRateIsIsolatedEnum value) noexcept {
    switch (value) {
    case GetFutureHourlyInterestRateIsIsolatedEnum::True_:
        return "TRUE";
    case GetFutureHourlyInterestRateIsIsolatedEnum::False_:
        return "FALSE";
    case GetFutureHourlyInterestRateIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

GetFutureHourlyInterestRateIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<GetFutureHourlyInterestRateIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return GetFutureHourlyInterestRateIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return GetFutureHourlyInterestRateIsIsolatedEnum::False_;
    }
    return GetFutureHourlyInterestRateIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetFutureHourlyInterestRateIsIsolatedEnum value) {
    if (value == GetFutureHourlyInterestRateIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "GetFutureHourlyInterestRateIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountBorrowRepayIsIsolatedEnum value) noexcept {
    switch (value) {
    case MarginAccountBorrowRepayIsIsolatedEnum::True_:
        return "TRUE";
    case MarginAccountBorrowRepayIsIsolatedEnum::False_:
        return "FALSE";
    case MarginAccountBorrowRepayIsIsolatedEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountBorrowRepayIsIsolatedEnum
tag_invoke(boost::json::value_to_tag<MarginAccountBorrowRepayIsIsolatedEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "TRUE") {
        return MarginAccountBorrowRepayIsIsolatedEnum::True_;
    }
    if (s == "FALSE") {
        return MarginAccountBorrowRepayIsIsolatedEnum::False_;
    }
    return MarginAccountBorrowRepayIsIsolatedEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountBorrowRepayIsIsolatedEnum value) {
    if (value == MarginAccountBorrowRepayIsIsolatedEnum::Unknown) {
        throw std::invalid_argument(
            "MarginAccountBorrowRepayIsIsolatedEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(MarginAccountBorrowRepayTypeEnum value) noexcept {
    switch (value) {
    case MarginAccountBorrowRepayTypeEnum::Borrow:
        return "BORROW";
    case MarginAccountBorrowRepayTypeEnum::Repay:
        return "REPAY";
    case MarginAccountBorrowRepayTypeEnum::Unknown:
        break;
    }
    return "";
}

MarginAccountBorrowRepayTypeEnum
tag_invoke(boost::json::value_to_tag<MarginAccountBorrowRepayTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BORROW") {
        return MarginAccountBorrowRepayTypeEnum::Borrow;
    }
    if (s == "REPAY") {
        return MarginAccountBorrowRepayTypeEnum::Repay;
    }
    return MarginAccountBorrowRepayTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                MarginAccountBorrowRepayTypeEnum value) {
    if (value == MarginAccountBorrowRepayTypeEnum::Unknown) {
        throw std::invalid_argument("MarginAccountBorrowRepayTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

std::string_view to_string(QueryBorrowRepayRecordsInMarginAccountTypeEnum value) noexcept {
    switch (value) {
    case QueryBorrowRepayRecordsInMarginAccountTypeEnum::Borrow:
        return "BORROW";
    case QueryBorrowRepayRecordsInMarginAccountTypeEnum::Repay:
        return "REPAY";
    case QueryBorrowRepayRecordsInMarginAccountTypeEnum::Unknown:
        break;
    }
    return "";
}

QueryBorrowRepayRecordsInMarginAccountTypeEnum
tag_invoke(boost::json::value_to_tag<QueryBorrowRepayRecordsInMarginAccountTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "BORROW") {
        return QueryBorrowRepayRecordsInMarginAccountTypeEnum::Borrow;
    }
    if (s == "REPAY") {
        return QueryBorrowRepayRecordsInMarginAccountTypeEnum::Repay;
    }
    return QueryBorrowRepayRecordsInMarginAccountTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                QueryBorrowRepayRecordsInMarginAccountTypeEnum value) {
    if (value == QueryBorrowRepayRecordsInMarginAccountTypeEnum::Unknown) {
        throw std::invalid_argument(
            "QueryBorrowRepayRecordsInMarginAccountTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

BorrowRepayApi::BorrowRepayApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest BorrowRepayApi::get_future_hourly_interest_rate_request(
    const GetFutureHourlyInterestRateParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/next-hourly-interest-rate";
    common::detail::json::set_param(req.query, "assets", params.assets);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<GetFutureHourlyInterestRateResponseInner>>
BorrowRepayApi::get_future_hourly_interest_rate(
    const GetFutureHourlyInterestRateParams& params) const {
    return common::send<std::vector<GetFutureHourlyInterestRateResponseInner>>(
        *client_, get_future_hourly_interest_rate_request(params));
}

common::RestRequest
BorrowRepayApi::get_interest_history_request(const GetInterestHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/interestHistory";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<GetInterestHistoryResponse>
BorrowRepayApi::get_interest_history(const GetInterestHistoryParams& params) const {
    return common::send<GetInterestHistoryResponse>(*client_, get_interest_history_request(params));
}

common::RestRequest BorrowRepayApi::margin_account_borrow_repay_request(
    const MarginAccountBorrowRepayParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Post;
    req.endpoint = "/sapi/v1/margin/borrow-repay";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "isIsolated", params.is_isolated);
    common::detail::json::set_param(req.query, "amount", params.amount);
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "symbol", params.symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<MarginAccountBorrowRepayResponse>
BorrowRepayApi::margin_account_borrow_repay(const MarginAccountBorrowRepayParams& params) const {
    return common::send<MarginAccountBorrowRepayResponse>(
        *client_, margin_account_borrow_repay_request(params));
}

common::RestRequest BorrowRepayApi::query_borrow_repay_records_in_margin_account_request(
    const QueryBorrowRepayRecordsInMarginAccountParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/borrow-repay";
    common::detail::json::set_param(req.query, "type", params.type);
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "txId", params.tx_id);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "current", params.current);
    common::detail::json::set_param(req.query, "size", params.size);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryBorrowRepayRecordsInMarginAccountResponse>
BorrowRepayApi::query_borrow_repay_records_in_margin_account(
    const QueryBorrowRepayRecordsInMarginAccountParams& params) const {
    return common::send<QueryBorrowRepayRecordsInMarginAccountResponse>(
        *client_, query_borrow_repay_records_in_margin_account_request(params));
}

common::RestRequest BorrowRepayApi::query_margin_interest_rate_history_request(
    const QueryMarginInterestRateHistoryParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/interestRateHistory";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "vipLevel", params.vip_level);
    common::detail::json::set_param(req.query, "startTime", params.start_time);
    common::detail::json::set_param(req.query, "endTime", params.end_time);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<std::vector<QueryMarginInterestRateHistoryResponseInner>>
BorrowRepayApi::query_margin_interest_rate_history(
    const QueryMarginInterestRateHistoryParams& params) const {
    return common::send<std::vector<QueryMarginInterestRateHistoryResponseInner>>(
        *client_, query_margin_interest_rate_history_request(params));
}

common::RestRequest
BorrowRepayApi::query_max_borrow_request(const QueryMaxBorrowParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/margin/maxBorrowable";
    common::detail::json::set_param(req.query, "asset", params.asset);
    common::detail::json::set_param(req.query, "isolatedSymbol", params.isolated_symbol);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = true;
    return req;
}

common::RestApiResponse<QueryMaxBorrowResponse>
BorrowRepayApi::query_max_borrow(const QueryMaxBorrowParams& params) const {
    return common::send<QueryMaxBorrowResponse>(*client_, query_max_borrow_request(params));
}

} // namespace binance::margin_trading::rest_api
