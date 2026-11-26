//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/margin_trading/export.hpp>
#include <binance/margin_trading/rest_api/models/get_cross_margin_transfer_history_response.hpp>
#include <binance/margin_trading/rest_api/models/query_max_transfer_out_amount_response.hpp>

namespace binance::margin_trading::rest_api {

enum class GetCrossMarginTransferHistoryTypeEnum {
    RollIn,
    RollOut,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_MARGIN_TRADING_EXPORT std::string_view
to_string(GetCrossMarginTransferHistoryTypeEnum value) noexcept;
BINANCE_MARGIN_TRADING_EXPORT GetCrossMarginTransferHistoryTypeEnum
tag_invoke(boost::json::value_to_tag<GetCrossMarginTransferHistoryTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_MARGIN_TRADING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              GetCrossMarginTransferHistoryTypeEnum value);

struct GetCrossMarginTransferHistoryParams {
    std::optional<std::string> asset = std::nullopt;
    std::optional<GetCrossMarginTransferHistoryTypeEnum> type = std::nullopt;
    std::optional<std::int64_t> start_time = std::nullopt;
    std::optional<std::int64_t> end_time = std::nullopt;
    std::optional<std::int64_t> current = std::nullopt;
    std::optional<std::int64_t> size = std::nullopt;
    std::optional<std::string> isolated_symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct QueryMaxTransferOutAmountParams {
    common::Required<std::string> asset;
    std::optional<std::string> isolated_symbol = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_MARGIN_TRADING_EXPORT TransferApi {
public:
    explicit TransferApi(std::shared_ptr<common::RestClient> client);

    /// Get Cross Margin Transfer History (USER_DATA)
    ///
    /// GET /sapi/v1/margin/transfer.
    ///
    /// Get Cross Margin Transfer History
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Response in descending order
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - Returns data for last 7 days by default
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/transfer#get-cross-margin-transfer-history
    [[nodiscard]] common::RestApiResponse<GetCrossMarginTransferHistoryResponse>
    get_cross_margin_transfer_history(const GetCrossMarginTransferHistoryParams& params = {}) const;

    /// Asynchronous `get_cross_margin_transfer_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetCrossMarginTransferHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_cross_margin_transfer_history(const GetCrossMarginTransferHistoryParams& params,
                                                 CompletionToken&& token) const {
        return common::async_send<GetCrossMarginTransferHistoryResponse>(
            client_, get_cross_margin_transfer_history_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Query Max Transfer-Out Amount (USER_DATA)
    ///
    /// GET /sapi/v1/margin/maxTransferable.
    ///
    /// Query Max Transfer-Out Amount
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - If isolatedSymbol is not sent, crossed margin data will be sent.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-margin-trading/api/rest-api/transfer#query-max-transfer-out-amount
    [[nodiscard]] common::RestApiResponse<QueryMaxTransferOutAmountResponse>
    query_max_transfer_out_amount(const QueryMaxTransferOutAmountParams& params) const;

    /// Asynchronous `query_max_transfer_out_amount()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<QueryMaxTransferOutAmountResponse>)`.
    template <class CompletionToken>
    auto async_query_max_transfer_out_amount(const QueryMaxTransferOutAmountParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<QueryMaxTransferOutAmountResponse>(
            client_, query_max_transfer_out_amount_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_cross_margin_transfer_history_request(
        const GetCrossMarginTransferHistoryParams& params) const;
    [[nodiscard]] common::RestRequest
    query_max_transfer_out_amount_request(const QueryMaxTransferOutAmountParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::margin_trading::rest_api
