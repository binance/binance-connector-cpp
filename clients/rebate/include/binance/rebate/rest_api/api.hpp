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
#include <binance/rebate/export.hpp>
#include <binance/rebate/rest_api/models/get_spot_rebate_history_records_response.hpp>

namespace binance::rebate::rest_api {

struct GetSpotRebateHistoryRecordsParams {
    /// Start time in milliseconds.
    std::optional<std::int64_t> start_time = std::nullopt;
    /// End time in milliseconds.
    std::optional<std::int64_t> end_time = std::nullopt;
    /// Page number.
    std::optional<std::int64_t> page = std::nullopt;
    /// Request validity window in milliseconds.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_REBATE_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::RestClient> client);

    /// Get Spot Rebate History Records (USER_DATA)
    ///
    /// GET /sapi/v1/rebate/taxQuery.
    ///
    /// Get Spot Rebate History Records
    ///
    /// Weight(UID): 12000
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - The max interval between `startTime` and `endTime` is 30 days.
    /// - If `startTime` and `endTime` are not sent, the recent 7 days' data will be returned.
    /// - The earliest supported `startTime` is June 10, 2020.
    /// - Return up to 200 records per request.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-rebate/api/rest-api/~#get-spot-rebate-history-records
    [[nodiscard]] common::RestApiResponse<GetSpotRebateHistoryRecordsResponse>
    get_spot_rebate_history_records(const GetSpotRebateHistoryRecordsParams& params = {}) const;

    /// Asynchronous `get_spot_rebate_history_records()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetSpotRebateHistoryRecordsResponse>)`.
    template <class CompletionToken>
    auto async_get_spot_rebate_history_records(const GetSpotRebateHistoryRecordsParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetSpotRebateHistoryRecordsResponse>(
            client_, get_spot_rebate_history_records_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    get_spot_rebate_history_records_request(const GetSpotRebateHistoryRecordsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::rebate::rest_api
