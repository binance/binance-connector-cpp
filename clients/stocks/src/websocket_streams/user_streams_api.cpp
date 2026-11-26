//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <cctype>
#include <charconv>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/stocks/websocket_streams/user_streams_api.hpp>

namespace binance::stocks::websocket_streams {

namespace {

// An all-digit id that fits 32 bits is sent as a number, anything else as a string.
common::StreamId to_stream_id(const std::string& id) {
    if (!id.empty() &&
        std::all_of(id.begin(), id.end(), [](unsigned char c) { return std::isdigit(c) != 0; })) {
        std::uint32_t number = 0;
        const auto [end, ec] = std::from_chars(id.data(), id.data() + id.size(), number);
        if (ec == std::errc() && end == id.data() + id.size()) {
            return number;
        }
    }
    return id;
}

// Fills the placeholders of `path` (`<symbol>@aggTrade`) from `params` and subscribes.
template <class T>
common::WebsocketStream<T> create_stream(common::WebsocketStreams& client, std::string_view path,
                                         const common::Params& params,
                                         std::optional<std::string> url_path) {
    std::map<std::string, std::string> variables;
    for (const auto& [key, value] : params) {
        variables.emplace(std::string(key), common::detail::param_to_string(value));
    }
    std::optional<common::StreamId> id;
    if (const auto it = variables.find("id"); it != variables.end()) {
        id = to_stream_id(it->second);
    }
    return common::WebsocketStream<T>(client.create_stream(
        common::detail::replace_websocket_streams_placeholders(path, variables), std::move(id),
        std::move(url_path)));
}

} // namespace

UserStreamsApi::UserStreamsApi(std::shared_ptr<common::WebsocketStreams> client)
    : client_(std::move(client)) {}

common::WebsocketStream<OrderReportStreamResponse>
UserStreamsApi::order_report_stream(const OrderReportStreamParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "listenKey", params.listen_key);
    common::detail::json::set_param(p, "id", params.id);
    return create_stream<OrderReportStreamResponse>(*client_, "<listenKey>@orderReport", p,
                                                    std::nullopt);
}

} // namespace binance::stocks::websocket_streams
