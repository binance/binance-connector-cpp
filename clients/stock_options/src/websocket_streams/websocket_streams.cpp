//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/stock_options/stock_options.hpp>
#include <binance/stock_options/websocket_streams/websocket_streams.hpp>

namespace binance::stock_options::websocket_streams {

namespace {

constexpr bool kHasTimeUnit = false;
constexpr bool kSignedStreams = false;

// Products without `timeUnit` support reject the query parameter.
common::WebsocketStreamsConfig normalize(common::WebsocketStreamsConfig configuration) {
    if constexpr (!kHasTimeUnit) {
        configuration.time_unit.reset();
    }
    return configuration;
}

std::shared_ptr<common::WebsocketStreams>
make_client(common::WebsocketStreamsConfig configuration) {
    // Signed streams authenticate the connection with the credentials in the configuration.
    common::detail::ClientOptions options{.user_agent =
                                              common::detail::build_user_agent(product_name()),
                                          .signed_streams = kSignedStreams,
                                          .stream_id_is_strictly_number = false};
    return std::make_shared<common::WebsocketStreams>(
        normalize(std::move(configuration)), std::vector<std::string>{}, std::move(options));
}

} // namespace

WebsocketStreamsConnection::WebsocketStreamsConnection(common::WebsocketStreamsConfig configuration)
    : client_(make_client(std::move(configuration))), user_streams_api_(client_) {}

WebsocketStreams::WebsocketStreams(common::WebsocketStreamsConfig configuration)
    : configuration_(std::move(configuration)) {}

} // namespace binance::stock_options::websocket_streams
