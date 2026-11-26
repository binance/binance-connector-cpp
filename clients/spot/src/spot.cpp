//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/spot/spot.hpp>

namespace binance::spot {

std::string_view product_name() noexcept {
    return "spot";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kSpotRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kSpotRestApiProdUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::testnet(common::RestApiConfig config) {
    config.base_path = common::constants::kSpotRestApiTestnetUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::demo(common::RestApiConfig config) {
    config.base_path = common::constants::kSpotRestApiDemoUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::from_config(common::WebsocketApiConfig config) {
    if (!config.url) {
        config.url = common::constants::kSpotWebsocketApiProdUrl;
    }
    return websocket_api::WebsocketApi(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::production(common::WebsocketApiConfig config) {
    config.url = common::constants::kSpotWebsocketApiProdUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi
websocket_api::WebsocketApi::testnet(common::WebsocketApiConfig config) {
    config.url = common::constants::kSpotWebsocketApiTestnetUrl;
    return from_config(std::move(config));
}

websocket_api::WebsocketApi websocket_api::WebsocketApi::demo(common::WebsocketApiConfig config) {
    config.url = common::constants::kSpotWebsocketApiDemoUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kSpotWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kSpotWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::testnet(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kSpotWebsocketStreamsTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::demo(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kSpotWebsocketStreamsDemoUrl;
    return from_config(std::move(config));
}

} // namespace binance::spot
