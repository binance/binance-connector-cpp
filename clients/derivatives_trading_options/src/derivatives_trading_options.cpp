//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/derivatives_trading_options/derivatives_trading_options.hpp>

namespace binance::derivatives_trading_options {

std::string_view product_name() noexcept {
    return "derivatives-trading-options";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kDerivativesTradingOptionsRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingOptionsRestApiProdUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::testnet(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingOptionsRestApiTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingOptionsWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingOptionsWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::testnet(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingOptionsWebsocketStreamsTestnetUrl;
    return from_config(std::move(config));
}

} // namespace binance::derivatives_trading_options
