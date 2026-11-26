//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <chrono>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/asio/any_completion_handler.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>

#include <binance/common/config.hpp>
#include <binance/common/export.hpp>
#include <binance/common/models.hpp>
#include <binance/common/websocket_common.hpp>
#include <binance/common/websocket_stream.hpp>

namespace binance::common {

/// The WebSocket market / user streams transport shared by every product.
///
/// - A pool of `mode.pool_size()` connections per URL path (e.g. `market`, `public`, `private`
///   for USDⓈ-M futures, or the base URL alone). Streams are spread over it round-robin, at
///   most 1024 per connection while another connection has room.
/// - Subscriptions made while no connection is open (reconnecting, or between `disconnect()` and
///   the next `connect()`) are kept, and sent once their connection opens.
/// - SUBSCRIBE and UNSUBSCRIBE made in one go (e.g. a loop of `create_stream`) are batched into
///   one request per connection when they are still queued (always, when made on the client's
///   executor). Nothing is delayed for it.
/// - Reconnects and 23 h renewals resubscribe through the connection URL; streams that do not
///   fit in it (about 4 KB) are subscribed once the connection opens. Signed streams have no
///   streams in their URL: they are all subscribed again by command once the connection opens.
/// - Around a renewal, a stream comes from the previous socket until the new one delivers it, so
///   a few messages may repeat.
/// - A SUBSCRIBE the server rejects drops its streams (`is_subscribed` turns false, they leave
///   reconnect URLs) and emits an `Error` event. Signed streams' commands have no id: each
///   acknowledgement answers the oldest command of its kind sent on that socket.
/// - Stream callbacks are keyed by `stream_key(stream, url_path)`. UNSUBSCRIBE is sent only once
///   no handle uses a stream.
/// - Streams of a connection that closes for good move to another connection of the pool, or
///   stay until the next `connect()` if none is left.
///
/// Threading, callbacks and destruction work as for `WebsocketApi`. Only `connect`,
/// `disconnect` and `wait_subscribed` wait for the executor (they throw if called on it).
class BINANCE_COMMON_EXPORT WebsocketStreams {
public:
    using ConnectSignature = void(std::exception_ptr);

    /// Throws `ConfigError` if `url` or `proxy` is invalid.
    explicit WebsocketStreams(WebsocketStreamsConfig configuration,
                              std::vector<std::string> url_paths = {},
                              detail::ClientOptions options = {});
    ~WebsocketStreams();
    WebsocketStreams(const WebsocketStreams&) = delete;
    WebsocketStreams& operator=(const WebsocketStreams&) = delete;
    WebsocketStreams(WebsocketStreams&&) = delete;
    WebsocketStreams& operator=(WebsocketStreams&&) = delete;

    /// The configuration, as given but without `private_key_passphrase` (the key is loaded).
    [[nodiscard]] const WebsocketStreamsConfig& configuration() const noexcept;
    [[nodiscard]] boost::asio::any_io_executor get_executor() const noexcept;

    /// Opens every connection that is not open. `streams` are subscribed through the URL of the
    /// first connection of each URL path, and survive reconnects like other subscriptions.
    template <class CompletionToken>
    auto async_connect(std::vector<std::string> streams, CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, ConnectSignature>(
            [this](auto handler, std::vector<std::string> s) {
                start_connect(std::move(s), boost::asio::any_completion_handler<ConnectSignature>(
                                                std::move(handler)));
            },
            token, std::move(streams));
    }
    void connect(std::vector<std::string> streams = {});

    /// Drops every subscription and callback (existing handles no longer do anything), then
    /// closes the connections like `WebsocketApi::disconnect`. Subscriptions made afterwards are
    /// sent by the next `connect()`.
    template <class CompletionToken> auto async_disconnect(CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, ConnectSignature>(
            [this](auto handler) {
                start_disconnect(
                    boost::asio::any_completion_handler<ConnectSignature>(std::move(handler)));
            },
            token);
    }
    void disconnect();

    [[nodiscard]] bool is_connected() const;
    void ping_server();

    template <class F> Subscription on_event(F&& callback, bool with_messages = true) {
        return add_event_callback(detail::bind_callback<WebsocketEvent>(std::forward<F>(callback)),
                                  with_messages);
    }

    /// Sends SUBSCRIBE for the streams not already subscribed, or queues them until their
    /// connection opens. `id` is normalised with `normalize_stream_id`. Throws `WebsocketError` for
    /// an empty stream name or a URL path the client was not created with.
    void subscribe(const std::vector<std::string>& streams, std::optional<StreamId> id = {},
                   const std::optional<std::string>& url_path = {});

    /// Sends UNSUBSCRIBE for the streams that no handle uses.
    void unsubscribe(const std::vector<std::string>& streams, std::optional<StreamId> id = {},
                     const std::optional<std::string>& url_path = {});

    /// True if `stream` is subscribed (or queued), on any URL path. Reflects `subscribe`,
    /// `unsubscribe`, `create_stream`, handle unsubscribes and `disconnect` as soon as they
    /// return, and a rejected SUBSCRIBE once its response arrives.
    [[nodiscard]] bool is_subscribed(const std::string& stream) const;

    /// Subscribes to `stream` and returns a handle for its callbacks. Data arriving before the
    /// first callback is added is kept for it (up to 1000 messages). Throws like `subscribe`.
    [[nodiscard]] WebsocketStreamHandle create_stream(std::string stream,
                                                      std::optional<StreamId> id = {},
                                                      std::optional<std::string> url_path = {});

    /// Completes once the server has acknowledged the subscription of `stream` (a SUBSCRIBE
    /// response, or a connection that opened with it in its URL), at once if it already has. It
    /// waits across reconnects and while the client is not connected yet. Fails with
    /// `WebsocketResponseError` if the server rejected the SUBSCRIBE, and with
    /// `WebsocketCancelledError` if the stream is not subscribed, or stops being before
    /// (unsubscribed, `disconnect()`, destruction of the client), or if the token's cancellation
    /// slot fires (any cancellation type; the subscription stays). `wait_subscribed` blocks and
    /// throws `WebsocketTimeoutError` once `timeout` passes, if given.
    template <class CompletionToken>
    auto async_wait_subscribed(std::string stream, std::optional<std::string> url_path,
                               CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, ConnectSignature>(
            [this](auto handler, std::string s, std::optional<std::string> path) {
                start_wait_subscribed(
                    std::move(s), std::move(path),
                    boost::asio::any_completion_handler<ConnectSignature>(std::move(handler)));
            },
            token, std::move(stream), std::move(url_path));
    }
    void wait_subscribed(std::string stream, std::optional<std::string> url_path = {},
                         std::optional<std::chrono::milliseconds> timeout = {});

    /// `url_path::stream`, or `stream` without a URL path.
    [[nodiscard]] static std::string stream_key(const std::string& stream,
                                                const std::optional<std::string>& url_path);

private:
    void start_connect(std::vector<std::string> streams,
                       boost::asio::any_completion_handler<ConnectSignature> handler);
    void start_disconnect(boost::asio::any_completion_handler<ConnectSignature> handler);
    void start_wait_subscribed(std::string stream, std::optional<std::string> url_path,
                               boost::asio::any_completion_handler<ConnectSignature> handler);
    Subscription add_event_callback(detail::Callback<WebsocketEvent> callback, bool with_messages);

    struct Impl;
    static void start_wait(const std::shared_ptr<Impl>& owner, std::string key,
                           boost::asio::any_completion_handler<ConnectSignature> handler);
    std::shared_ptr<Impl> impl_;
};

} // namespace binance::common
