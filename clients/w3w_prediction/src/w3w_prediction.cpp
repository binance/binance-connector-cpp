//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/w3w_prediction/w3w_prediction.hpp>

namespace binance::w3w_prediction {

std::string_view product_name() noexcept {
    return "w3w-prediction";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kW3WPredictionRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kW3WPredictionRestApiProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kW3WPredictionWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kW3WPredictionWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

} // namespace binance::w3w_prediction
