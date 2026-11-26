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
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/pay/export.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryParams {
    /// Start time in milliseconds.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time in milliseconds.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Number of records to return.
    std::optional<std::int64_t> limit = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_PAY_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::RestClient> client);

    /// Get Pay Trade History
    ///
    /// GET /sapi/v1/pay/transactions.
    ///
    /// Get Pay Trade History
    ///
    /// Weight(UID): 3000
    ///
    /// Notes:
    /// - If `startTime` and `endTime` are not sent, the recent 90 days' data will be returned.
    /// - The max interval between `startTime` and `endTime` is 90 days.
    /// - Support for querying orders within the last 18 months.
    /// - `payerInfo` and `receiverInfo` return different fields in different `orderType` values:
    ///   - C2C sender: `payerInfo=binanceId`; `receiverInfo=name,
    ///   binanceId/accountId/email/countryCode/phoneNumber/mobileCode` (based on user input).
    ///   - C2C receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - CRYPTO_BOX sender: `payerInfo=binanceId`; `receiverInfo=name` (always `"Crypto Box"`).
    ///   - CRYPTO_BOX receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - PAY sender: `payerInfo=binanceId`; `receiverInfo=name`.
    ///   - PAY receiver: `payerInfo=name`; `receiverInfo=binanceId, name`.
    ///   - PAY_REFUND sender: `payerInfo=binanceId, name`; `receiverInfo=name, accountId`.
    ///   - PAY_REFUND receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - PAYOUT sender: `payerInfo=binanceId, name`; `receiverInfo=name, accountId`.
    ///   - PAYOUT receiver: `payerInfo=name`; `receiverInfo=binanceId`.
    ///   - CRYPTO_BOX_RF receiver: `payerInfo=name` (always `"Crypto Box"`);
    ///   `receiverInfo=binanceId`.
    ///   - REMITTANCE sender: `payerInfo=binanceId`; `receiverInfo=name, institutionName,
    ///   cardNumber, digitalWalletId`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-pay/api/rest-api/~#get-pay-trade-history
    [[nodiscard]] common::RestApiResponse<GetPayTradeHistoryResponse>
    get_pay_trade_history(const GetPayTradeHistoryParams& params = {}) const;

    /// Asynchronous `get_pay_trade_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetPayTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_pay_trade_history(const GetPayTradeHistoryParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetPayTradeHistoryResponse>(
            client_, get_pay_trade_history_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_pay_trade_history_request(const GetPayTradeHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::pay::rest_api
