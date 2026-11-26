//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/derivatives_trading_portfolio_margin/derivatives_trading_portfolio_margin.hpp>

namespace binance::derivatives_trading_portfolio_margin {

std::string_view product_name() noexcept {
    return "derivatives-trading-portfolio-margin";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kDerivativesTradingPortfolioMarginRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingPortfolioMarginRestApiProdUrl;
    return from_config(std::move(config));
}

rest_api::RestApi rest_api::RestApi::testnet(common::RestApiConfig config) {
    config.base_path = common::constants::kDerivativesTradingPortfolioMarginRestApiTestnetUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::from_config(common::WebsocketStreamsConfig config) {
    if (!config.url) {
        config.url = common::constants::kDerivativesTradingPortfolioMarginWebsocketStreamsProdUrl;
    }
    return websocket_streams::WebsocketStreams(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::production(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingPortfolioMarginWebsocketStreamsProdUrl;
    return from_config(std::move(config));
}

websocket_streams::WebsocketStreams
websocket_streams::WebsocketStreams::testnet(common::WebsocketStreamsConfig config) {
    config.url = common::constants::kDerivativesTradingPortfolioMarginWebsocketStreamsTestnetUrl;
    return from_config(std::move(config));
}

} // namespace binance::derivatives_trading_portfolio_margin
