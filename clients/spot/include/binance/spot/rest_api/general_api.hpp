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

#include <binance/common/rest.hpp>
#include <binance/spot/export.hpp>
#include <binance/spot/rest_api/models/exchange_info_response.hpp>
#include <binance/spot/rest_api/models/execution_rules_response.hpp>
#include <binance/spot/rest_api/models/time_response.hpp>

namespace binance::spot::rest_api {

enum class ExchangeInfoPermissionsEnum {
    Spot,
    Margin,
    Leveraged,
    TrdGrp002,
    TrdGrp003,
    TrdGrp004,
    TrdGrp005,
    TrdGrp006,
    TrdGrp007,
    TrdGrp008,
    TrdGrp009,
    TrdGrp010,
    TrdGrp011,
    TrdGrp012,
    TrdGrp013,
    TrdGrp014,
    TrdGrp015,
    TrdGrp016,
    TrdGrp017,
    TrdGrp018,
    TrdGrp019,
    TrdGrp020,
    TrdGrp021,
    TrdGrp022,
    TrdGrp023,
    TrdGrp024,
    TrdGrp025,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_SPOT_EXPORT std::string_view
to_string(ExchangeInfoPermissionsEnum value) noexcept;
BINANCE_SPOT_EXPORT ExchangeInfoPermissionsEnum tag_invoke(
    boost::json::value_to_tag<ExchangeInfoPermissionsEnum> /*tag*/, const boost::json::value& jv);
BINANCE_SPOT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    ExchangeInfoPermissionsEnum value);

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
    /// Example: curl -X GET "https://api.binance.com/api/v3/exchangeInfo?symbol=BNBBTC"
    std::optional<std::string> symbol = std::nullopt;
    /// Examples: curl -X GET
    /// "https://api.binance.com/api/v3/exchangeInfo?symbols=%5B%22BNBBTC%22,%22BTCUSDT%22%5D" or
    /// curl -g -X GET 'https://api.binance.com/api/v3/exchangeInfo?symbols=["BTCUSDT","BNBBTC"]'
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Examples: curl -X GET "https://api.binance.com/api/v3/exchangeInfo?permissions=SPOT"  curl
    /// -X GET
    /// "https://api.binance.com/api/v3/exchangeInfo?permissions=%5B%22MARGIN%22%2C%22LEVERAGED%22%5D"
    /// or curl -g -X GET
    /// 'https://api.binance.com/api/v3/exchangeInfo?permissions=["MARGIN","LEVERAGED"]'
    std::optional<std::vector<ExchangeInfoPermissionsEnum>> permissions = std::nullopt;
    /// Controls whether the content of the `permissionSets` field is populated or not.
    std::optional<bool> show_permission_sets = std::nullopt;
    /// Filters for symbols that have this `tradingStatus`. Cannot be used in combination with
    /// `symbols` or `symbol`.
    std::optional<ExchangeInfoSymbolStatusEnum> symbol_status = std::nullopt;
};

struct ExecutionRulesParams {
    /// Query for specified symbol.
    std::optional<std::string> symbol = std::nullopt;
    /// Query for multiple symbols.
    std::optional<std::vector<std::string>> symbols = std::nullopt;
    /// Query for all symbols with the specified status.
    std::optional<ExecutionRulesSymbolStatusEnum> symbol_status = std::nullopt;
};

class BINANCE_SPOT_EXPORT GeneralApi {
public:
    explicit GeneralApi(std::shared_ptr<common::RestClient> client);

    /// Exchange information
    ///
    /// GET /api/v3/exchangeInfo.
    ///
    /// Current exchange trading rules and symbol information
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
    /// * `permissions` can support single or multiple values (e.g. `SPOT`,
    /// `["MARGIN","LEVERAGED"]`). This cannot be used in combination with `symbol` or `symbols`.
    /// * If `permissions` parameter not provided, all symbols that have either `SPOT`, `MARGIN`, or
    /// `LEVERAGED` permission will be exposed.
    ///   * To display symbols with any permission you need to specify them explicitly in
    ///   `permissions`: (e.g. `["SPOT","MARGIN",...]`.). See Account and Symbol Permissions for the
    ///   full list.
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
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#exchange-info
    [[nodiscard]] common::RestApiResponse<ExchangeInfoResponse>
    exchange_info(const ExchangeInfoParams& params = {}) const;

    /// Asynchronous `exchange_info()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExchangeInfoResponse>)`.
    template <class CompletionToken>
    auto async_exchange_info(const ExchangeInfoParams& params, CompletionToken&& token) const {
        return common::async_send<ExchangeInfoResponse>(client_, exchange_info_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// Query Execution Rules
    ///
    /// GET /api/v3/executionRules.
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
    /// **Note:**: No combination of multiple parameters is allowed.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#execution-rules
    [[nodiscard]] common::RestApiResponse<ExecutionRulesResponse>
    execution_rules(const ExecutionRulesParams& params = {}) const;

    /// Asynchronous `execution_rules()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<ExecutionRulesResponse>)`.
    template <class CompletionToken>
    auto async_execution_rules(const ExecutionRulesParams& params, CompletionToken&& token) const {
        return common::async_send<ExecutionRulesResponse>(client_, execution_rules_request(params),
                                                          std::forward<CompletionToken>(token));
    }

    /// Test connectivity
    ///
    /// GET /api/v3/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#ping
    [[nodiscard]] common::RestApiResponse<boost::json::value> ping() const;

    /// Asynchronous `ping()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken> auto async_ping(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, ping_request(),
                                                      std::forward<CompletionToken>(token));
    }

    /// Check server time
    ///
    /// GET /api/v3/time.
    ///
    /// Test connectivity to the Rest API and get the current server time.
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: NONE
    ///
    /// Notes:
    /// **Data Source:** Memory
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-spot-trading/api/rest-api/general#time
    [[nodiscard]] common::RestApiResponse<TimeResponse> time() const;

    /// Asynchronous `time()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<TimeResponse>)`.
    template <class CompletionToken> auto async_time(CompletionToken&& token) const {
        return common::async_send<TimeResponse>(client_, time_request(),
                                                std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest exchange_info_request(const ExchangeInfoParams& params) const;
    [[nodiscard]] common::RestRequest
    execution_rules_request(const ExecutionRulesParams& params) const;
    [[nodiscard]] common::RestRequest ping_request() const;
    [[nodiscard]] common::RestRequest time_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::spot::rest_api
