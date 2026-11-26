//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <string_view>

#include <binance/cms/export.hpp>
#include <binance/cms/websocket_streams/websocket_streams.hpp>
#include <binance/common/config.hpp>

namespace binance::cms {

// Declared in every module header. A block rather than NOLINTNEXTLINE: clang-format wraps the
// declaration when the export macro is long.
// NOLINTBEGIN(readability-redundant-declaration)
/// Product identifier used in the User-Agent.
[[nodiscard]] BINANCE_CMS_EXPORT std::string_view product_name() noexcept;
// NOLINTEND(readability-redundant-declaration)

/// The Cms WebSocket streams client, created with `CmsWebsocketStreams::production(config)`
/// and the other factories of `websocket_streams::WebsocketStreams`.
using CmsWebsocketStreams = websocket_streams::WebsocketStreams;
using CmsWebsocketStreamsConnection = websocket_streams::WebsocketStreamsConnection;
using CmsWsStreams = CmsWebsocketStreams;
using CmsWsStreamsConnection = CmsWebsocketStreamsConnection;

} // namespace binance::cms
