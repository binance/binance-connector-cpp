//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/derivatives_trading_coin_futures/derivatives_trading_coin_futures.hpp>
#include <binance/derivatives_trading_coin_futures/rest_api/rest_api.hpp>

namespace binance::derivatives_trading_coin_futures::rest_api {

RestApi::RestApi(common::RestApiConfig configuration)
    : client_(std::make_shared<common::RestClient>(
          std::move(configuration),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      account_api_(client_), market_data_api_(client_), trade_api_(client_),
      user_data_streams_api_(client_) {}

const common::RestApiConfig& RestApi::configuration() const noexcept {
    return client_->configuration();
}

} // namespace binance::derivatives_trading_coin_futures::rest_api
