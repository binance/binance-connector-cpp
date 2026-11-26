//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <memory>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/cms/export.hpp>
#include <binance/cms/websocket_streams/models/com_announcement_en_response.hpp>
#include <binance/common/websocket_streams.hpp>

namespace binance::cms::websocket_streams {

/// Each method subscribes to one stream (or queues the subscription while the connection
/// reconnects) and returns its handle. Destroying the handle, or calling `unsubscribe()` on it,
/// ends the subscription.
class BINANCE_CMS_EXPORT Api {
public:
    explicit Api(std::shared_ptr<common::WebsocketStreams> client);

    /// `com_announcement_en`.
    ///
    /// Receive push notifications hen Binance publishes announcements in English (language code:
    /// en).
    ///
    /// See https://developers.binance.com/en/docs/products/announcements/announcement
    [[nodiscard]] common::WebsocketStream<ComAnnouncementEnResponse> com_announcement_en() const;

private:
    std::shared_ptr<common::WebsocketStreams> client_;
};

} // namespace binance::cms::websocket_streams
