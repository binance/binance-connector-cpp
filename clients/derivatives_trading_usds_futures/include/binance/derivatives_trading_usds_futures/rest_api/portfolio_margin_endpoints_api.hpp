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

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/classic_portfolio_margin_account_information_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct ClassicPortfolioMarginAccountInformationParams {
    common::Required<std::string> asset;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT PortfolioMarginEndpointsApi {
public:
    explicit PortfolioMarginEndpointsApi(std::shared_ptr<common::RestClient> client);

    /// Classic Portfolio Margin Account Information (USER_DATA)
    ///
    /// GET /fapi/v1/pmAccountInfo.
    ///
    /// Get Classic Portfolio Margin current account information.
    ///
    /// Weight(IP): 5
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - maxWithdrawAmount is for asset transfer out to the spot wallet.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/portfolio-margin-endpoints#classic-portfolio-margin-account-information
    [[nodiscard]] common::RestApiResponse<ClassicPortfolioMarginAccountInformationResponse>
    classic_portfolio_margin_account_information(
        const ClassicPortfolioMarginAccountInformationParams& params) const;

    /// Asynchronous `classic_portfolio_margin_account_information()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<ClassicPortfolioMarginAccountInformationResponse>)`.
    template <class CompletionToken>
    auto async_classic_portfolio_margin_account_information(
        const ClassicPortfolioMarginAccountInformationParams& params,
        CompletionToken&& token) const {
        return common::async_send<ClassicPortfolioMarginAccountInformationResponse>(
            client_, classic_portfolio_margin_account_information_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest classic_portfolio_margin_account_information_request(
        const ClassicPortfolioMarginAccountInformationParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_usds_futures::rest_api
