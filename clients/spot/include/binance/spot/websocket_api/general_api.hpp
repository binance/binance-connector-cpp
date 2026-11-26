//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/websocket_api.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/websocket_api/models/exchange_info_response.hpp>
#include <binance/spot/websocket_api/models/execution_rules_response_result.hpp>
#include <binance/spot/websocket_api/models/time_response_result.hpp>

namespace binance::spot::websocket_api {

enum class ExchangeInfoSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(ExchangeInfoSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT ExchangeInfoSymbolStatusEnum tag_invoke(
    boost::json::value_to_tag<ExchangeInfoSymbolStatusEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    ExchangeInfoSymbolStatusEnum value);

enum class ExecutionRulesSymbolStatusEnum {
    Trading,
    Halt,
    Break,
    CancelOnly,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(ExecutionRulesSymbolStatusEnum value) noexcept;
BINANCE_SPOT_EXPORT ExecutionRulesSymbolStatusEnum
tag_invoke(boost::json::value_to_tag<ExecutionRulesSymbolStatusEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    ExecutionRulesSymbolStatusEnum value);

struct ExchangeInfoParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Describe a single symbol
    std::optional<std::string> symbol = std::nullopt;
    /// Describe multiple symbols
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Filter symbols by permissions
    std::optional<std::vector<std::string>> permissions = std::nullopt;
    /// Controls whether the content of the `permissionSets` field is populated or not. Defaults to
    /// `true`.
    std::optional<bool> show_permission_sets = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. Valid values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`. Cannot be used in combination with `symbol` or `symbols`.
    std::optional<ExchangeInfoSymbolStatusEnum> symbol_status = std::nullopt;
};

struct ExecutionRulesParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
    /// Query for specified symbol.
    std::optional<std::string> symbol = std::nullopt;
    /// Query for multiple symbols.
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Query for all symbols with the specified status. Supported values: `TRADING`, `HALT`,
    /// `BREAK`, `CANCEL_ONLY`
    std::optional<ExecutionRulesSymbolStatusEnum> symbol_status = std::nullopt;
};

struct PingParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

struct TimeParams {
    /// Client-generated request identifier.
    std::optional<std::string> id = std::nullopt;
};

class BINANCE_SPOT_EXPORT GeneralApi {
public:
    explicit GeneralApi(std::shared_ptr<common::WebsocketApi> client);

    /// Exchange information
    ///
    /// `exchangeInfo`.
    ///
    /// Query current exchange trading rules, rate limits, and symbol
    /// information.
    ///
    /// Weight(IP): 20
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// **Notes:**
    /// * If the value provided to `symbol` or `symbols` do not exist, the endpoint will throw an
    /// error saying the symbol is invalid.
    /// * All parameters are optional.
    /// * Only one of `symbol`, `symbols`, `permissions` parameters can be specified.
    /// * Without parameters, `exchangeInfo` displays all symbols with `["SPOT", "MARGIN",
    /// "LEVERAGED"]` permissions.
    ///   * In order to list *all* active symbols on the exchange, you need to explicitly request
    ///   all permissions.
    /// * `permissions` accepts either a list of permissions, or a single permission name. E.g.
    /// `"SPOT"`.
    ///
    /// **Examples of Symbol Permissions Interpretation from the Response:**
    ///
    /// * `[["A","B"]]` means you may place an order if your account has either permission "A"
    /// **or** permission "B".
    /// * `[["A"],["B"]]` means you can place an order if your account has permission "A" **and**
    /// permission "B".
    /// * `[["A"],["B","C"]]` means you can place an order if your account has permission "A"
    /// **and** permission "B" or permission "C". (Inclusive or is applied here, not exclusive or,
    /// so your account may have both permission "B" and permission "C".)
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#exchange-info
    [[nodiscard]] common::WebsocketApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const;

    /// Asynchronous `exchange_info()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<ExchangeInfoResponse>)`.
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return common::async_send<ExchangeInfoResponse>(
            client_, "exchangeInfo", exchange_info_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Query Execution Rules
    ///
    /// `executionRules`.
    ///
    /// Query execution rules for symbols.
    ///
    /// Weight: Parameter | Weight
    /// --- | ---
    /// `symbol` | 2
    /// `symbols` | 2 for each `symbol`, capped at a max of 40
    /// `symbolStatus` | 40
    /// None | 40
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// **Note:** No combination of multiple parameters is allowed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#execution-rules
    [[nodiscard]] common::WebsocketApiResponse<ExecutionRulesResponseResult>
    execution_rules(const ExecutionRulesParams& params = {}) const;

    /// Asynchronous `execution_rules()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<ExecutionRulesResponseResult>)`.
    template <class CompletionToken>
    auto async_execution_rules(const ExecutionRulesParams& params, CompletionToken&& token) const {
        return common::async_send<ExecutionRulesResponseResult>(
            client_, "executionRules", execution_rules_payload(params),
            make_options(false, false, false, false), std::forward<CompletionToken>(token));
    }

    /// Test connectivity
    ///
    /// `ping`.
    ///
    /// Test connectivity to the WebSocket API.
    ///
    /// Note: You can use regular WebSocket ping frames to test connectivity as well, WebSocket API
    /// will respond with pong frames as soon as possible. ping request along with time is a safe
    /// way to test request-response handling in your application.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#ping
    [[nodiscard]] common::WebsocketApiResponse<boost::json::value>
    ping(const PingParams& params = {}) const;

    /// Asynchronous `ping()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<boost::json::value>)`.
    template <class CompletionToken>
    auto async_ping(const PingParams& params, CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, "ping", ping_payload(params),
                                                      make_options(false, false, false, false),
                                                      std::forward<CompletionToken>(token));
    }

    /// Check server time
    ///
    /// `time`.
    ///
    /// Test connectivity to the WebSocket API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/ws-api/general#time
    [[nodiscard]] common::WebsocketApiResponse<TimeResponseResult>
    time(const TimeParams& params = {}) const;

    /// Asynchronous `time()`. Completes with
    /// `void(std::exception_ptr, common::WebsocketApiResponse<TimeResponseResult>)`.
    template <class CompletionToken>
    auto async_time(const TimeParams& params, CompletionToken&& token) const {
        return common::async_send<TimeResponseResult>(client_, "time", time_payload(params),
                                                      make_options(false, false, false, false),
                                                      std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] static common::Params exchange_info_payload(const ExchangeInfoParams& params);
    [[nodiscard]] static common::Params execution_rules_payload(const ExecutionRulesParams& params);
    [[nodiscard]] static common::Params ping_payload(const PingParams& params);
    [[nodiscard]] static common::Params time_payload(const TimeParams& params);
    [[nodiscard]] static common::WebsocketMessageSendOptions
    make_options(bool with_api_key, bool is_signed, bool is_session_logon, bool is_session_logout) {
        common::WebsocketMessageSendOptions options;
        options.with_api_key = with_api_key;
        options.is_signed = is_signed;
        options.is_session_logon = is_session_logon;
        options.is_session_logout = is_session_logout;
        return options;
    }

    std::shared_ptr<common::WebsocketApi> client_;
};

} // namespace binance::spot::websocket_api
