//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_portfolio_margin/export.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

class BINANCE_DERIVATIVES_TRADING_PORTFOLIO_MARGIN_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Test Connectivity
    ///
    /// GET /papi/v1/ping.
    ///
    /// Test connectivity to the Rest API.
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-derivatives-trading-portfolio-margin/api/rest-api/market-data#test-connectivity
    [[nodiscard]] common::RestApiResponse<boost::json::value> test_connectivity() const;

    /// Asynchronous `test_connectivity()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<boost::json::value>)`.
    template <class CompletionToken> auto async_test_connectivity(CompletionToken&& token) const {
        return common::async_send<boost::json::value>(client_, test_connectivity_request(),
                                                      std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest test_connectivity_request() const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
