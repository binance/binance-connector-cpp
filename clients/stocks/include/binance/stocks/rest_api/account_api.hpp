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
#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/sign_us_equity_disclaimer_response.hpp>

namespace binance::stocks::rest_api {

struct SignUsEquityDisclaimerParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCKS_EXPORT AccountApi {
public:
    explicit AccountApi(std::shared_ptr<common::RestClient> client);

    /// Sign US Equity Disclaimer (TRADE)
    ///
    /// POST /sapi/v1/equity/account/disclaimer.
    ///
    /// Records the user's acknowledgement and acceptance of the US equity disclaimer. This must be
    /// completed before the account can access certain US equity trading features. The acceptance
    /// is tied to the account associated with the API key.
    ///
    /// Weight: 1
    ///
    /// Security Type: TRADE
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stocks-trading/api/rest-api/account#sign-us-equity-disclaimer
    [[nodiscard]] common::RestApiResponse<SignUsEquityDisclaimerResponse>
    sign_us_equity_disclaimer(const SignUsEquityDisclaimerParams& params = {}) const;

    /// Asynchronous `sign_us_equity_disclaimer()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SignUsEquityDisclaimerResponse>)`.
    template <class CompletionToken>
    auto async_sign_us_equity_disclaimer(const SignUsEquityDisclaimerParams& params,
                                         CompletionToken&& token) const {
        return common::async_send<SignUsEquityDisclaimerResponse>(
            client_, sign_us_equity_disclaimer_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    sign_us_equity_disclaimer_request(const SignUsEquityDisclaimerParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stocks::rest_api
