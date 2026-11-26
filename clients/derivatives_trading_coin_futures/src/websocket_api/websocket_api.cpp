//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/derivatives_trading_coin_futures/derivatives_trading_coin_futures.hpp>
#include <binance/derivatives_trading_coin_futures/websocket_api/websocket_api.hpp>

namespace binance::derivatives_trading_coin_futures::websocket_api {

namespace {

constexpr bool kHasTimeUnit = false;

// Products without `timeUnit` support reject the query parameter.
common::WebsocketApiConfig normalize(common::WebsocketApiConfig configuration) {
    if constexpr (!kHasTimeUnit) {
        configuration.time_unit.reset();
    }
    return configuration;
}

} // namespace

WebsocketApiConnection::WebsocketApiConnection(common::WebsocketApiConfig configuration)
    : client_(std::make_shared<common::WebsocketApi>(
          normalize(std::move(configuration)),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      account_api_(client_), trade_api_(client_), user_data_streams_api_(client_) {}

WebsocketApi::WebsocketApi(common::WebsocketApiConfig configuration)
    : configuration_(std::move(configuration)) {}

} // namespace binance::derivatives_trading_coin_futures::websocket_api
