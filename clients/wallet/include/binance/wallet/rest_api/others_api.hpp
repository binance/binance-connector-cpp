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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/get_symbols_delist_schedule_for_spot_response_inner.hpp>
#include <binance/wallet/rest_api/models/system_status_response.hpp>

namespace binance::wallet::rest_api {

struct GetSymbolsDelistScheduleForSpotParams {
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_WALLET_EXPORT OthersApi {
public:
    explicit OthersApi(std::shared_ptr<common::RestClient> client);

    /// Get Spot Delist Schedule (MARKET_DATA)
    ///
    /// GET /sapi/v1/spot/delist-schedule.
    ///
    /// Get symbols delist schedule for spot
    ///
    /// Weight(IP): 100
    ///
    /// Security Type: MARKET_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/others#get-symbols-delist-schedule-for-spot
    [[nodiscard]] common::RestApiResponse<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>
    get_symbols_delist_schedule_for_spot(
        const GetSymbolsDelistScheduleForSpotParams& params = {}) const;

    /// Asynchronous `get_symbols_delist_schedule_for_spot()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>)`.
    template <class CompletionToken>
    auto
    async_get_symbols_delist_schedule_for_spot(const GetSymbolsDelistScheduleForSpotParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<std::vector<GetSymbolsDelistScheduleForSpotResponseInner>>(
            client_, get_symbols_delist_schedule_for_spot_request(params),
            std::forward<CompletionToken>(token));
    }

    /// System Status
    ///
    /// GET /sapi/v1/system/status.
    ///
    /// Fetch system status.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: System
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-wallet/api/rest-api/others#system-status
    [[nodiscard]] common::RestApiResponse<SystemStatusResponse> system_status() const;

    /// Asynchronous `system_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SystemStatusResponse>)`.
    template <class CompletionToken> auto async_system_status(CompletionToken&& token) const {
        return common::async_send<SystemStatusResponse>(client_, system_status_request(),
                                                        std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_symbols_delist_schedule_for_spot_request(
        const GetSymbolsDelistScheduleForSpotParams& params) const;
    [[nodiscard]] common::RestRequest system_status_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::wallet::rest_api
