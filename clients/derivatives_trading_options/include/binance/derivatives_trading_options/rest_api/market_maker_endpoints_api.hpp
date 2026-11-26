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
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_options/export.hpp>
#include <binance/derivatives_trading_options/rest_api/models/auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/get_auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/get_market_maker_protection_config_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/reset_market_maker_protection_config_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/set_auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/set_market_maker_protection_config_response.hpp>

namespace binance::derivatives_trading_options::rest_api {

struct AutoCancelAllOpenOrdersParams {
    common::Required<std::string> underlyings;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetAutoCancelAllOpenOrdersParams {
    /// Underlying asset.
    std::optional<std::string> underlying = std::nullopt;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetAutoCancelAllOpenOrdersParams {
    common::Required<std::string> underlying;
    /// Countdown time in milliseconds (ex. 1,000 for 1 second). 0 to disable the timer. Negative
    /// values (ex. -10000) are not accepted. Minimum acceptable value is 5,000
    common::Required<std::int64_t> countdown_time;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetMarketMakerProtectionConfigParams {
    /// Underlying asset.
    common::Required<std::string> underlying;
    /// Recv Window.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ResetMarketMakerProtectionConfigParams {
    common::Required<std::string> underlying;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SetMarketMakerProtectionConfigParams {
    common::Required<std::string> underlying;
    /// MMP Interval in milliseconds
    common::Required<std::int64_t> window_time_in_milliseconds;
    /// MMP frozen time in milliseconds, if set to 0 manual reset is required
    common::Required<std::int64_t> frozen_time_in_milliseconds;
    /// quantity limit
    common::Required<common::Decimal> qty_limit;
    /// net delta limit
    common::Required<common::Decimal> delta_limit;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_OPTIONS_EXPORT MarketMakerEndpointsApi {
public:
    explicit MarketMakerEndpointsApi(std::shared_ptr<common::RestClient> client);

    /// Auto-Cancel All Open Orders (Kill-Switch) Heartbeat (TRADE)
    ///
    /// POST /eapi/v1/countdownCancelAllHeartBeat.
    ///
    /// This endpoint resets the time from which the countdown will begin to the time this messaged
    /// is received.  It should be called repeatedly as heartbeats.  Multiple heartbeats can be
    /// updated at once by specifying the underlying symbols as a list (ex. BTCUSDT,ETHUSDT) in the
    /// underlyings parameter.
    ///
    /// Weight(IP): 10
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - The response will only include underlying symbols where the heartbeat has been
    /// successfully updated.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<AutoCancelAllOpenOrdersResponse>
    auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params) const;

    /// Asynchronous `auto_cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AutoCancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_auto_cancel_all_open_orders(const AutoCancelAllOpenOrdersParams& params,
                                           CompletionToken&& token) const {
        return common::async_send<AutoCancelAllOpenOrdersResponse>(
            client_, auto_cancel_all_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Auto-Cancel All Open Orders (Kill-Switch) Config (TRADE)
    ///
    /// GET /eapi/v1/countdownCancelAll.
    ///
    /// This endpoint returns the auto-cancel parameters for each underlying symbol. Note only
    /// active auto-cancel parameters will be returned, if countdownTime is set to 0 (ie.
    /// countdownTime has been turned off), the underlying symbol and corresponding countdownTime
    /// parameter will not be returned in the response.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - countdownTime = 0 means the function is disabled.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#get-auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<GetAutoCancelAllOpenOrdersResponse>
    get_auto_cancel_all_open_orders(const GetAutoCancelAllOpenOrdersParams& params = {}) const;

    /// Asynchronous `get_auto_cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetAutoCancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_get_auto_cancel_all_open_orders(const GetAutoCancelAllOpenOrdersParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<GetAutoCancelAllOpenOrdersResponse>(
            client_, get_auto_cancel_all_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set Auto-Cancel All Open Orders (Kill-Switch) Config (TRADE)
    ///
    /// POST /eapi/v1/countdownCancelAll.
    ///
    /// This endpoint sets the parameters of the auto-cancel feature which cancels all open orders
    /// (both market maker protection and non market maker protection order types) of the underlying
    /// symbol at the end of the specified countdown time period if no heartbeat message is sent.
    /// After the countdown time period, all open orders will be cancelled. The auto-cancel feature
    /// can be turned off by setting countdownTime to 0.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - This rest endpoint sets up the parameters to cancel your open orders in case of an outage
    /// or disconnection.
    /// - Example usage: > Call this endpoint with a countdownTime value of 10000 (10 seconds) to
    /// turn on the auto-cancel feature. If the corresponding countdownCancelAllHeartBeat endpoint
    /// is not called within 10 seconds with the specified underlying symbol, all open orders of the
    /// specified symbol will be automatically canceled. If this endpoint is called with an
    /// countdownTime of 0, the countdown timer will be stopped.
    /// - The system will check all countdowns approximately every 100 milliseconds, **please note
    /// that sufficient redundancy should be considered when using this function**. We do not
    /// recommend setting the countdown time to be too precise or too small.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#set-auto-cancel-all-open-orders
    [[nodiscard]] common::RestApiResponse<SetAutoCancelAllOpenOrdersResponse>
    set_auto_cancel_all_open_orders(const SetAutoCancelAllOpenOrdersParams& params) const;

    /// Asynchronous `set_auto_cancel_all_open_orders()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetAutoCancelAllOpenOrdersResponse>)`.
    template <class CompletionToken>
    auto async_set_auto_cancel_all_open_orders(const SetAutoCancelAllOpenOrdersParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<SetAutoCancelAllOpenOrdersResponse>(
            client_, set_auto_cancel_all_open_orders_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Market Maker Protection Config (TRADE)
    ///
    /// GET /eapi/v1/mmp.
    ///
    /// Get config for MMP.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#get-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<GetMarketMakerProtectionConfigResponse>
    get_market_maker_protection_config(const GetMarketMakerProtectionConfigParams& params) const;

    /// Asynchronous `get_market_maker_protection_config()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetMarketMakerProtectionConfigResponse>)`.
    template <class CompletionToken>
    auto
    async_get_market_maker_protection_config(const GetMarketMakerProtectionConfigParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetMarketMakerProtectionConfigResponse>(
            client_, get_market_maker_protection_config_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Reset Market Maker Protection Config (TRADE)
    ///
    /// POST /eapi/v1/mmpReset.
    ///
    /// Reset MMP, start MMP order again.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#reset-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<ResetMarketMakerProtectionConfigResponse>
    reset_market_maker_protection_config(
        const ResetMarketMakerProtectionConfigParams& params) const;

    /// Asynchronous `reset_market_maker_protection_config()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<ResetMarketMakerProtectionConfigResponse>)`.
    template <class CompletionToken>
    auto
    async_reset_market_maker_protection_config(const ResetMarketMakerProtectionConfigParams& params,
                                               CompletionToken&& token) const {
        return common::async_send<ResetMarketMakerProtectionConfigResponse>(
            client_, reset_market_maker_protection_config_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Set Market Maker Protection Config (TRADE)
    ///
    /// POST /eapi/v1/mmpSet.
    ///
    /// Set config for MMP. Market Maker Protection(MMP) is a set of protection mechanism for option
    /// market maker, this mechanism is able to prevent mass trading in short period time. Once
    /// market maker's account branches the threshold, the Market Maker Protection will be
    /// triggered. When Market Maker Protection triggers, all the current MMP orders will be
    /// canceled, new MMP orders will be rejected. Market maker can use this time to reevaluate
    /// market and modify order price.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-options/api/rest-api/market-maker-endpoints#set-market-maker-protection-config
    [[nodiscard]] common::RestApiResponse<SetMarketMakerProtectionConfigResponse>
    set_market_maker_protection_config(const SetMarketMakerProtectionConfigParams& params) const;

    /// Asynchronous `set_market_maker_protection_config()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SetMarketMakerProtectionConfigResponse>)`.
    template <class CompletionToken>
    auto
    async_set_market_maker_protection_config(const SetMarketMakerProtectionConfigParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<SetMarketMakerProtectionConfigResponse>(
            client_, set_market_maker_protection_config_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    auto_cancel_all_open_orders_request(const AutoCancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    get_auto_cancel_all_open_orders_request(const GetAutoCancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest
    set_auto_cancel_all_open_orders_request(const SetAutoCancelAllOpenOrdersParams& params) const;
    [[nodiscard]] common::RestRequest get_market_maker_protection_config_request(
        const GetMarketMakerProtectionConfigParams& params) const;
    [[nodiscard]] common::RestRequest reset_market_maker_protection_config_request(
        const ResetMarketMakerProtectionConfigParams& params) const;
    [[nodiscard]] common::RestRequest set_market_maker_protection_config_request(
        const SetMarketMakerProtectionConfigParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_options::rest_api
