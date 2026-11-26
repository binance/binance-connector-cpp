//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/stock_options/stock_options.hpp>

namespace binance::stock_options {

std::string_view product_name() noexcept {
    return "stock-options";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kStockOptionsRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kStockOptionsRestApiProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kStockOptionsWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kStockOptionsWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

} // namespace binance::stock_options
