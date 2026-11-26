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
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/c2c/export.hpp>
#include <binance/c2c/rest_api/models/get_c2c_trade_history_response.hpp>
#include <binance/common/rest.hpp>

namespace binance::c2c::rest_api {

enum class GetC2CTradeHistoryTradeTypeEnum {
    Buy,
    Sell,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_C2C_EXPORT std::string_view
to_string(GetC2CTradeHistoryTradeTypeEnum value) noexcept;
BINANCE_C2C_EXPORT GetC2CTradeHistoryTradeTypeEnum
tag_invoke(boost::json::value_to_tag<GetC2CTradeHistoryTradeTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_C2C_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   GetC2CTradeHistoryTradeTypeEnum value);

struct GetC2CTradeHistoryParams {
    /// Trade side filter
    std::optional<GetC2CTradeHistoryTradeTypeEnum> trade_type = std::nullopt;
    std::optional<std::int64_t> start_timestamp = std::nullopt;
    std::optional<std::int64_t> end_timestamp = std::nullopt;
    /// Page number
    std::optional<std::int64_t> page = std::nullopt;
    /// Number of records per page
    std::optional<std::int64_t> rows = std::nullopt;
};

class BINANCE_C2C_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::RestClient> client);

    /// Get C2C Trade History (USER_DATA)
    ///
    /// GET /sapi/v1/c2c/orderMatch/listUserOrderHistory.
    ///
    /// Get C2C (also known as P2P) trade history, including both buy and sell orders.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The max interval between `startTimestamp` and `endTimestamp` is 30 days.
    /// - If `startTimestamp` and `endTimestamp` are not sent, the recent 30 days' data is returned.
    /// - You can only view data from the past 6 months. For all C2C orders, check
    /// `https://c2c.binance.com/en/fiatOrder`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-c2-c/api/rest-api/~#get-c2-ctrade-history
    [[nodiscard]] common::RestApiResponse<GetC2CTradeHistoryResponse>
    get_c2c_trade_history(const GetC2CTradeHistoryParams& params = {}) const;

    /// Asynchronous `get_c2c_trade_history()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetC2CTradeHistoryResponse>)`.
    template <class CompletionToken>
    auto async_get_c2c_trade_history(const GetC2CTradeHistoryParams& params,
                                     CompletionToken&& token) const {
        return common::async_send<GetC2CTradeHistoryResponse>(
            client_, get_c2c_trade_history_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_c2c_trade_history_request(const GetC2CTradeHistoryParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::c2c::rest_api
