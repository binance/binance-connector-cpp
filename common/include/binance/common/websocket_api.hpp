//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <boost/asio/any_completion_handler.hpp>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/bind_executor.hpp>

#include <binance/common/config.hpp>
#include <binance/common/export.hpp>
#include <binance/common/models.hpp>
#include <binance/common/signer.hpp>
#include <binance/common/websocket_common.hpp>
#include <binance/common/websocket_stream.hpp>

namespace binance::common {

/// A user-data subscription: the response to its request, and the stream receiving its events.
struct [[nodiscard]] WebsocketApiRawSubscription {
    WebsocketApiRawResponse response;
    WebsocketStreamHandle stream;
};

/// A typed user-data subscription: the response decoded as `T`, events as `E`.
template <class T, class E> struct [[nodiscard]] WebsocketApiSubscription {
    WebsocketApiResponse<T> response;
    WebsocketStream<E> stream;
};

/// The WebSocket API transport (request / response) shared by every product.
///
/// - A pool of `mode.pool_size()` connections, used round-robin.
/// - Requests are matched to responses by `id` and time out after `timeout`.
/// - Dropped connections reconnect after `reconnect_delay`, unless the close code says it is
///   permanent (see `WebsocketConnectionFailureReason`).
/// - Connections are renewed every 23 hours, and when the server announces `serverShutdown`,
///   without losing in-flight requests.
/// - With `auto_session_relogon`, a session logged on with `session.logon` is logged on again
///   after every reconnect.
/// - User-data subscriptions made with `subscribe` are sent again after every reconnect and
///   renewal (after the session logon, if any), on the connection that made them. Their stream
///   ends them (see `async_subscribe`).
/// - Other requests about subscriptions (`userDataStream.unsubscribe`, `session.subscriptions`)
///   sent with `send_message` go to one connection, like any request, and Binance numbers the
///   subscriptions of each connection from 0: with `pool_size() > 1`, end a subscription through
///   its stream. A successful `userDataStream.unsubscribe` also stops sending the subscriptions it
///   ended again.
///
/// The client runs on its own I/O thread, or on `configuration.executor` when set. Completion
/// handlers run on their associated executor, or on the client's (`get_executor()`). Callbacks
/// (events, user data) run on the client's executor unless bound to another, so they should not
/// block. Every member function is thread-safe. Blocking calls (`connect`, `disconnect`,
/// `send_message`, `subscribe`) throw `WebsocketError` if made from the client's executor or a
/// thread running it (for `io_context` and `thread_pool` executors and their strands); with other
/// executors, do not make them from its threads. The other calls never block on the executor.
///
/// Errors are `WebsocketError` subclasses, or `ConnectorClientError` for a request that cannot be
/// built (missing `api_key`, signing failure).
///
/// Destroying the client closes its connections at once and fails pending requests with
/// `WebsocketCancelledError`; call `disconnect()` first for a graceful close.
class BINANCE_COMMON_EXPORT WebsocketApi {
public:
    using ConnectSignature = void(std::exception_ptr);
    using SendSignature = void(std::exception_ptr, std::vector<WebsocketApiRawResponse>);
    using SubscribeSignature = void(std::exception_ptr, WebsocketApiRawSubscription);

    /// Throws `ConfigError` if `url` or `proxy` is invalid, or `ConnectorClientError` if the
    /// private key cannot be loaded.
    explicit WebsocketApi(WebsocketApiConfig configuration, detail::ClientOptions options = {});
    ~WebsocketApi();
    WebsocketApi(const WebsocketApi&) = delete;
    WebsocketApi& operator=(const WebsocketApi&) = delete;
    WebsocketApi(WebsocketApi&&) = delete;
    WebsocketApi& operator=(WebsocketApi&&) = delete;

    /// The configuration, as given but without `private_key_passphrase` (the key is loaded).
    [[nodiscard]] const WebsocketApiConfig& configuration() const noexcept;
    [[nodiscard]] const SignatureGenerator& signature_generator() const noexcept;
    [[nodiscard]] boost::asio::any_io_executor get_executor() const noexcept;

    /// Opens every connection of the pool that is not open, each within `connect_timeout`.
    /// Completes once all are open, or with the first failure. A call made while connecting
    /// completes with that attempt; one made while disconnecting connects once that is done.
    template <class CompletionToken> auto async_connect(CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, ConnectSignature>(
            [this](auto handler) {
                start_connect(
                    boost::asio::any_completion_handler<ConnectSignature>(std::move(handler)));
            },
            token);
    }
    void connect();

    /// Stops reconnecting, waits up to 30 s for pending responses, then closes every connection
    /// with code 1000. The session logon is forgotten.
    template <class CompletionToken> auto async_disconnect(CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, ConnectSignature>(
            [this](auto handler) {
                start_disconnect(
                    boost::asio::any_completion_handler<ConnectSignature>(std::move(handler)));
            },
            token);
    }
    void disconnect();

    /// True if at least one connection is open.
    [[nodiscard]] bool is_connected() const;

    /// Sends a ping frame on every open connection.
    void ping_server();

    /// Registers a lifecycle callback (`WebsocketEvent`). It runs on its associated executor if
    /// it has one, else on the client's executor. `Message` events are built and delivered only
    /// if some callback has `with_messages`.
    template <class F> Subscription on_event(F&& callback, bool with_messages = true) {
        return add_event_callback(detail::bind_callback<WebsocketEvent>(std::forward<F>(callback)),
                                  with_messages);
    }

    /// Sends a request and completes with its response: one per connection for
    /// `is_session_logon` / `is_session_logout` (sent on every connection), else exactly one.
    ///
    /// Supports per-operation cancellation (`bind_cancellation_slot`, `cancel_after(timer, …)`):
    /// it then completes with `WebsocketCancelledError`. A response that arrives later is
    /// dropped, but the request may still have been executed.
    template <class CompletionToken>
    auto async_send_message(std::string method, Params payload, WebsocketMessageSendOptions options,
                            CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, SendSignature>(
            [this](auto handler, std::string m, Params p, WebsocketMessageSendOptions o) {
                start_send(std::move(m), std::move(p), o,
                           boost::asio::any_completion_handler<SendSignature>(std::move(handler)));
            },
            token, std::move(method), std::move(payload), options);
    }

    /// Blocking `async_send_message`.
    std::vector<WebsocketApiRawResponse> send_message(std::string method, Params payload,
                                                      WebsocketMessageSendOptions options = {});

    /// Sends a request that opens a user-data subscription (e.g. `userDataStream.subscribe`)
    /// and completes with its response and a stream of its events (`{"event": {...}}`
    /// messages from that subscription). The client sends the request again whenever the
    /// connection reopens, and the server may then assign another `subscriptionId`.
    /// `stream.unsubscribe()`, or destroying the stream, ends the subscription: it sends
    /// `userDataStream.unsubscribe` with the current `subscriptionId` on the connection holding
    /// it, and stops sending the request again. Failures are reported as `Error` events.
    /// `stream.stream()` is the first `subscriptionId`. Per-operation cancellation is not
    /// supported: it completes with the response.
    template <class CompletionToken>
    auto async_subscribe(std::string method, Params payload, WebsocketMessageSendOptions options,
                         CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, SubscribeSignature>(
            [this](auto handler, std::string m, Params p, WebsocketMessageSendOptions o) {
                start_subscribe(
                    std::move(m), std::move(p), o,
                    boost::asio::any_completion_handler<SubscribeSignature>(std::move(handler)));
            },
            token, std::move(method), std::move(payload), options);
    }

    /// Blocking `async_subscribe`.
    WebsocketApiRawSubscription subscribe(std::string method, Params payload,
                                          WebsocketMessageSendOptions options = {});

    /// A handle receiving every user-data event from any connection, for subscriptions managed
    /// by the caller. `id` names it; it defaults to a random one. While a connection is renewed,
    /// both of its sockets deliver, so an event may arrive twice. Prefer `subscribe`.
    [[nodiscard]] WebsocketStreamHandle create_stream(std::string id = {});

private:
    void start_connect(boost::asio::any_completion_handler<ConnectSignature> handler);
    void start_disconnect(boost::asio::any_completion_handler<ConnectSignature> handler);
    void start_send(std::string method, Params payload, WebsocketMessageSendOptions options,
                    boost::asio::any_completion_handler<SendSignature> handler);
    void start_subscribe(std::string method, Params payload, WebsocketMessageSendOptions options,
                         boost::asio::any_completion_handler<SubscribeSignature> handler);
    Subscription add_event_callback(detail::Callback<WebsocketEvent> callback, bool with_messages);

    struct Impl;
    std::shared_ptr<Impl> impl_;
};

namespace detail {

template <class Result, class Convert, class CompletionToken>
auto async_send_as(std::shared_ptr<WebsocketApi> api, std::string method, Params payload,
                   WebsocketMessageSendOptions options, Convert convert, CompletionToken&& token) {
    return boost::asio::async_initiate<CompletionToken, void(std::exception_ptr, Result)>(
        [](auto handler, std::shared_ptr<WebsocketApi> a, std::string m, Params p,
           WebsocketMessageSendOptions o, Convert c) {
            auto ex = boost::asio::get_associated_executor(handler, a->get_executor());
            auto slot = boost::asio::get_associated_cancellation_slot(handler);
            auto* raw = a.get();
            raw->async_send_message(
                std::move(m), std::move(p), o,
                boost::asio::bind_cancellation_slot(
                    slot,
                    boost::asio::bind_executor(
                        std::move(ex), [h = std::move(handler), a = std::move(a), c = std::move(c)](
                                           std::exception_ptr ep,
                                           std::vector<WebsocketApiRawResponse> responses) mutable {
                            Result out;
                            if (!ep) {
                                out = c(std::move(responses));
                            }
                            std::move(h)(ep, std::move(out));
                        })));
        },
        token, std::move(api), std::move(method), std::move(payload), options, std::move(convert));
}

template <class T> WebsocketApiResponse<T> first_response(std::vector<WebsocketApiRawResponse> r) {
    return r.empty() ? WebsocketApiResponse<T>() : WebsocketApiResponse<T>(std::move(r.front()));
}

template <class T>
std::vector<WebsocketApiResponse<T>> all_responses(std::vector<WebsocketApiRawResponse> r) {
    std::vector<WebsocketApiResponse<T>> out;
    out.reserve(r.size());
    for (auto& raw : r) {
        out.emplace_back(std::move(raw));
    }
    return out;
}

template <class T, class E> WebsocketApiSubscription<T, E> typed(WebsocketApiRawSubscription s) {
    return {WebsocketApiResponse<T>(std::move(s.response)),
            WebsocketStream<E>(std::move(s.stream))};
}

} // namespace detail

/// Blocking typed `WebsocketApi::subscribe`: the response decoded as `T`, events as `E`.
template <class T, class E>
WebsocketApiSubscription<T, E> subscribe(WebsocketApi& api, std::string method, Params payload,
                                         WebsocketMessageSendOptions options = {}) {
    return detail::typed<T, E>(api.subscribe(std::move(method), std::move(payload), options));
}

/// Asynchronous typed subscribe, completing with
/// `void(std::exception_ptr, WebsocketApiSubscription<T, E>)`. `api` is
/// kept alive until it completes.
template <class T, class E, class CompletionToken>
auto async_subscribe(std::shared_ptr<WebsocketApi> api, std::string method, Params payload,
                     WebsocketMessageSendOptions options, CompletionToken&& token) {
    using Result = WebsocketApiSubscription<T, E>;
    return boost::asio::async_initiate<CompletionToken, void(std::exception_ptr, Result)>(
        [](auto handler, std::shared_ptr<WebsocketApi> a, std::string m, Params p,
           WebsocketMessageSendOptions o) {
            auto ex = boost::asio::get_associated_executor(handler, a->get_executor());
            auto* raw = a.get();
            raw->async_subscribe(std::move(m), std::move(p), o,
                                 boost::asio::bind_executor(
                                     std::move(ex), [h = std::move(handler), a = std::move(a)](
                                                        std::exception_ptr ep,
                                                        WebsocketApiRawSubscription s) mutable {
                                         Result out;
                                         if (!ep) {
                                             out = detail::typed<T, E>(std::move(s));
                                         }
                                         std::move(h)(ep, std::move(out));
                                     }));
        },
        token, std::move(api), std::move(method), std::move(payload), options);
}

/// Blocking typed send of a regular request.
template <class T>
WebsocketApiResponse<T> send(WebsocketApi& api, std::string method, Params payload,
                             WebsocketMessageSendOptions options = {}) {
    return detail::first_response<T>(
        api.send_message(std::move(method), std::move(payload), options));
}

/// Blocking typed send of a request answered by every connection (`session.logon` /
/// `session.logout`): one response per connection.
template <class T>
std::vector<WebsocketApiResponse<T>> send_all(WebsocketApi& api, std::string method, Params payload,
                                              WebsocketMessageSendOptions options = {}) {
    return detail::all_responses<T>(
        api.send_message(std::move(method), std::move(payload), options));
}

/// Asynchronous typed send of a regular request, completing with
/// `void(std::exception_ptr, WebsocketApiResponse<T>)`. `api` is kept alive until it completes.
template <class T, class CompletionToken>
auto async_send(std::shared_ptr<WebsocketApi> api, std::string method, Params payload,
                WebsocketMessageSendOptions options, CompletionToken&& token) {
    return detail::async_send_as<WebsocketApiResponse<T>>(
        std::move(api), std::move(method), std::move(payload), options, &detail::first_response<T>,
        std::forward<CompletionToken>(token));
}

/// Asynchronous `send_all`, completing with
/// `void(std::exception_ptr, std::vector<WebsocketApiResponse<T>>)`.
template <class T, class CompletionToken>
auto async_send_all(std::shared_ptr<WebsocketApi> api, std::string method, Params payload,
                    WebsocketMessageSendOptions options, CompletionToken&& token) {
    return detail::async_send_as<std::vector<WebsocketApiResponse<T>>>(
        std::move(api), std::move(method), std::move(payload), options, &detail::all_responses<T>,
        std::forward<CompletionToken>(token));
}

} // namespace binance::common
