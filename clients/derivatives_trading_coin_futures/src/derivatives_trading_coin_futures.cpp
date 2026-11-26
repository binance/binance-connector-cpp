//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/derivatives_trading_coin_futures/derivatives_trading_coin_futures.hpp>

namespace binance::derivatives_trading_coin_futures {

std::string_view product_name() noexcept {
    return "derivatives-trading-coin-futures";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kDerivativesTradingCoinFuturesRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingCoinFuturesRestApiProdUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::testnet(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingCoinFuturesRestApiTestnetUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::demo(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingCoinFuturesRestApiDemoUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::from_config(common::WebsocketApiConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketApiProdUrl;
    }
    return websocket_api::WebsocketApi(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::production(common::WebsocketApiConfig config) {
    config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketApiProdUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::testnet(common::WebsocketApiConfig config) {
    config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketApiTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::testnet(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketStreamsTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::demo(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingCoinFuturesWebsocketStreamsDemoUrl;
    return from_config(std::move(config));
}

} // namespace binance::derivatives_trading_coin_futures
