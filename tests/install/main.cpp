//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <iostream>
#include <string_view>
#include <vector>

#include <binance/common/rest.hpp>
#include <binance/common/version.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/common/websocket_streams.hpp>

std::vector<std::string_view> installed_products();

int main() {
    // Constructing clients exercises the installed headers, export macros and link dependencies
    // without touching the network: the URLs only need to be well formed (.invalid never resolves).
    binance::common::RestApiConfig rest_cfg;
    rest_cfg.base_path = "https://example.invalid";
    rest_cfg.proxy_from_env = false;
    const binance::common::RestClient rest(rest_cfg);

    binance::common::WebsocketApiConfig api_cfg;
    api_cfg.url = "wss://example.invalid/ws";
    api_cfg.proxy_from_env = false;
    const binance::common::WebsocketApi api(api_cfg);

    binance::common::WebsocketStreamsConfig streams_cfg;
    streams_cfg.url = "wss://example.invalid";
    streams_cfg.proxy_from_env = false;
    const binance::common::WebsocketStreams streams(streams_cfg);

    std::cout << "binance-connector-cpp " << binance::common::sdk_version() << '\n';
    for (const auto name : installed_products()) {
        if (name.empty()) {
            std::cerr << "a product has no name\n";
            return 1;
        }
        std::cout << "  " << name << '\n';
    }
    return binance::common::sdk_version() == binance::common::kVersion ? 0 : 1;
}
