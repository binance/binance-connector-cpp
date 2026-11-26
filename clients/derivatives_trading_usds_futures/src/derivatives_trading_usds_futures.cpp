//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/derivatives_trading_usds_futures/derivatives_trading_usds_futures.hpp>

namespace binance::derivatives_trading_usds_futures {

std::string_view product_name() noexcept {
    return "derivatives-trading-usds-futures";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kDerivativesTradingUsdsFuturesRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingUsdsFuturesRestApiProdUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::testnet(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingUsdsFuturesRestApiTestnetUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::demo(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingUsdsFuturesRestApiDemoUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::from_config(common::WebsocketApiConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketApiProdUrl;
    }
    return websocket_api::WebsocketApi(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::production(common::WebsocketApiConfig config) {
    config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketApiProdUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::testnet(common::WebsocketApiConfig config) {
    config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketApiTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::testnet(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketStreamsTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::demo(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingUsdsFuturesWebsocketStreamsDemoUrl;
    return from_config(std::move(config));
}

} // namespace binance::derivatives_trading_usds_futures
