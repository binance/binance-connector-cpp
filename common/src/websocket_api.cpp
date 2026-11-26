//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <atomic>

#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/json/serialize.hpp>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/websocket_api.hpp>

#include "utils.hpp"
#include "websocket_common.hpp"

namespace binance::common {

namespace asio = boost::asio;
namespace json = boost::json;

namespace {

const std::string& require_url(const std::optional<std::string>& url) {
    if (!url || url->empty()) {
        throw ConfigError("Configuration missing or invalid `url`");
    }
    return *url;
}

detail::WebsocketSettings settings_for(const WebsocketApiConfig& cfg, std::string user_agent) {
    detail::WebsocketSettings s;
    s.name = "WebsocketApi";
    s.reconnect_delay = cfg.reconnect_delay;
    s.connect_timeout = cfg.connect_timeout;
    s.compression = cfg.compression;
    s.max_message_size = cfg.max_message_size;
    s.is_pool = cfg.mode.is_pool();
    s.proxy = cfg.proxy;
    s.proxy_from_env = cfg.proxy_from_env;
    s.agent = cfg.agent;
    s.transport = cfg.transport;
    s.user_agent = detail::user_agent_or_default(std::move(user_agent));
    s.executor = cfg.executor;
    return s;
}

std::optional<RateLimitType> rate_limit_type_from(std::string_view s) {
    if (s == "REQUEST_WEIGHT") {
        return RateLimitType::RequestWeight;
    }
    if (s == "ORDERS") {
        return RateLimitType::Orders;
    }
    if (s == "RAW_REQUESTS") {
        return RateLimitType::RawRequests;
    }
    return std::nullopt;
}

std::optional<Interval> interval_from(std::string_view s) {
    if (s == "SECOND") {
        return Interval::Second;
    }
    if (s == "MINUTE") {
        return Interval::Minute;
    }
    if (s == "HOUR") {
        return Interval::Hour;
    }
    if (s == "DAY") {
        return Interval::Day;
    }
    return std::nullopt;
}

std::optional<std::uint32_t> u32_from(const json::value* v) {
    if (v == nullptr) {
        return std::nullopt;
    }
    if (v->is_uint64() && v->get_uint64() <= UINT32_MAX) {
        return static_cast<std::uint32_t>(v->get_uint64());
    }
    if (v->is_int64() && v->get_int64() >= 0 && v->get_int64() <= UINT32_MAX) {
        return static_cast<std::uint32_t>(v->get_int64());
    }
    return std::nullopt;
}

/// `rateLimits`, skipping entries that do not parse.
std::optional<std::vector<WebsocketApiRateLimit>> parse_rate_limits(const json::object& msg) {
    const auto* v = msg.if_contains("rateLimits");
    if (v == nullptr || !v->is_array()) {
        return std::nullopt;
    }
    std::vector<WebsocketApiRateLimit> out;
    for (const auto& entry : v->get_array()) {
        const auto* obj = entry.if_object();
        if (obj == nullptr) {
            continue;
        }
        const auto* type = obj->if_contains("rateLimitType");
        const auto* interval = obj->if_contains("interval");
        if (type == nullptr || !type->is_string() || interval == nullptr ||
            !interval->is_string()) {
            continue;
        }
        const auto t = rate_limit_type_from(type->get_string());
        const auto i = interval_from(interval->get_string());
        const auto num = u32_from(obj->if_contains("intervalNum"));
        const auto limit = u32_from(obj->if_contains("limit"));
        if (!t || !i || !num || !limit) {
            continue;
        }
        out.push_back({*t, *i, *num, *limit, u32_from(obj->if_contains("count")).value_or(0)});
    }
    return out;
}

std::int64_t int_or(const json::value* v, std::int64_t fallback) {
    if (v != nullptr && v->is_int64()) {
        return v->get_int64();
    }
    if (v != nullptr && v->is_uint64() && v->get_uint64() <= INT64_MAX) {
        return static_cast<std::int64_t>(v->get_uint64());
    }
    return fallback;
}

/// A response object to a `WebsocketApiRawResponse`, or the `WebsocketResponseError` it carries.
WebsocketApiRawResponse to_raw_response(json::object msg) {
    auto rate_limits = parse_rate_limits(msg);
    const auto status = int_or(msg.if_contains("status"), 0);
    if (status >= 400) {
        std::int64_t code = status;
        std::string text = "Unknown error";
        std::optional<std::chrono::system_clock::time_point> retry_at;
        std::shared_ptr<const json::value> data;
        if (const auto* err = msg.if_contains("error"); err != nullptr && err->is_object()) {
            code = int_or(err->get_object().if_contains("code"), status);
            if (const auto* m = err->get_object().if_contains("msg");
                m != nullptr && m->is_string()) {
                text = m->get_string();
            }
            if (const auto* d = err->get_object().if_contains("data");
                d != nullptr && !d->is_null()) {
                if (d->is_object()) {
                    if (const auto ms = int_or(d->get_object().if_contains("retryAfter"), -1);
                        ms >= 0) {
                        retry_at =
                            std::chrono::system_clock::time_point(std::chrono::milliseconds(ms));
                    }
                }
                // Kept whole, as Binance sent it.
                data = std::make_shared<const json::value>(*d);
            }
        }
        throw WebsocketResponseError(code, text, static_cast<std::uint16_t>(status),
                                     rate_limits.value_or(std::vector<WebsocketApiRateLimit>{}),
                                     retry_at, std::move(data));
    }
    WebsocketApiRawResponse out;
    if (auto* r = msg.if_contains("result")) {
        out.result = std::move(*r);
    } else if (auto* r2 = msg.if_contains("response")) {
        out.result = std::move(*r2);
    }
    out.rate_limits = std::move(rate_limits);
    return out;
}

/// Ends a user-data subscription on the server, given its `subscriptionId`.
constexpr std::string_view kUserDataUnsubscribe = "userDataStream.unsubscribe";

std::optional<json::value> subscription_id_of(const json::value& result) {
    if (const auto* obj = result.if_object()) {
        if (const auto* id = obj->if_contains("subscriptionId")) {
            return *id;
        }
    }
    return std::nullopt;
}

std::string describe(const std::exception_ptr& ep) {
    try {
        std::rethrow_exception(ep);
    } catch (const std::exception& e) {
        return e.what();
    } catch (...) {
        return "unknown error";
    }
}

} // namespace

struct WebsocketApi::Impl final : detail::WebsocketCommon {
    Impl(WebsocketApiConfig configuration, std::string user_agent)
        : WebsocketCommon(settings_for(configuration, std::move(user_agent)),
                          require_url(configuration.url), configuration.mode.pool_size()),
          cfg(std::move(configuration)),
          signer(cfg.api_secret, cfg.private_key, cfg.private_key_passphrase) {
        signer.load_key();
        // The signer keeps the parsed key, so the passphrase is not kept in the configuration.
        cfg.private_key_passphrase.reset();
    }

    /// A user-data subscription, or a `create_stream` handle (no `request`), which gets every
    /// event.
    struct UserData {
        detail::StreamListeners listeners;
        /// The request that made the subscription, sent again after reconnects and renewals.
        std::optional<detail::SessionLogon> request;
        detail::Connection* connection = nullptr;
        /// The socket the subscription lives on: events from others are duplicates.
        const detail::Socket* socket = nullptr;
        std::optional<json::value> subscription_id;
    };

    struct Targets {
        std::vector<detail::Connection*> connections;
        bool skip_auth = false;
    };

    using SubscribeDone =
        std::function<void(std::exception_ptr, WebsocketApiRawResponse, std::uint64_t)>;

    WebsocketApiConfig cfg;
    SignatureGenerator signer;
    std::map<std::uint64_t, UserData> user_data;
    std::atomic<std::uint64_t> next_user_data_id{0};

    [[nodiscard]] std::string prepare_url(const std::string& url) const {
        if (!cfg.time_unit) {
            return url;
        }
        const auto sep = url.find('?') == std::string::npos ? '?' : '&';
        return url + sep + "timeUnit=" + std::string(to_lower_string(*cfg.time_unit));
    }

    std::string reconnect_url(detail::Connection& /*conn*/) override {
        return prepare_url(*cfg.url);
    }

    /// Sends one request on each of `targets` and calls `done` with every response (in order),
    /// or the first error. `on_cancel`, if given, is set to forget the request.
    void send_on(
        const std::vector<detail::Connection*>& targets, const std::string& method,
        const Params& payload, const WebsocketMessageSendOptions& options, bool skip_auth,
        const std::function<void(std::exception_ptr, std::vector<WebsocketApiRawResponse>)>& done,
        std::function<void()>* on_cancel = nullptr) {
        auto [id, request] =
            detail::build_websocket_api_message(cfg, signer, method, payload, options, skip_auth);
        if (on_cancel != nullptr) {
            *on_cancel = [this, targets, request_id = id] {
                for (auto* conn : targets) {
                    drop_request(*conn, request_id);
                }
            };
        }
        if (Logger::enabled(LogLevel::Debug)) {
            Logger::debug("WebsocketApi: sending " +
                          json::serialize(detail::redact_request(request)));
        }
        const auto text = json::serialize(request);

        struct State {
            std::vector<std::optional<WebsocketApiRawResponse>> responses;
            std::size_t remaining = 0;
            std::exception_ptr error;
            std::function<void(std::exception_ptr, std::vector<WebsocketApiRawResponse>)> done;
        };
        auto state = std::make_shared<State>();
        state->responses.resize(targets.size());
        state->remaining = targets.size();
        state->done = done;

        auto finish_one = [state](std::size_t index, std::exception_ptr ep,
                                  std::optional<WebsocketApiRawResponse> response) {
            if (ep && !state->error) {
                state->error = ep;
            }
            state->responses[index] = std::move(response);
            if (--state->remaining != 0) {
                return;
            }
            std::vector<WebsocketApiRawResponse> out;
            if (!state->error) {
                out.reserve(state->responses.size());
                for (auto& r : state->responses) {
                    out.push_back(std::move(*r));
                }
            }
            state->done(state->error, std::move(out));
        };

        for (std::size_t i = 0; i < targets.size(); ++i) {
            try {
                send_request(*targets[i], id, text, cfg.timeout,
                             [finish_one, i](std::exception_ptr ep, json::object msg) {
                                 if (ep) {
                                     finish_one(i, ep, std::nullopt);
                                     return;
                                 }
                                 try {
                                     finish_one(i, nullptr, to_raw_response(std::move(msg)));
                                 } catch (...) {
                                     finish_one(i, std::current_exception(), std::nullopt);
                                 }
                             });
            } catch (...) {
                finish_one(i, std::current_exception(), std::nullopt);
            }
        }
    }

    /// Every open connection for a session logon / logout, else the next one. Throws
    /// `WebsocketNotConnectedError`.
    Targets select_targets(const WebsocketMessageSendOptions& options) {
        Targets out;
        if (options.is_session_logon || options.is_session_logout) {
            out.connections = available_connections(false, std::nullopt);
            std::erase_if(out.connections, [](const auto* c) { return c->socket == nullptr; });
            if (out.connections.empty()) {
                throw WebsocketNotConnectedError();
            }
        } else {
            auto& conn = get_connection(false, std::nullopt);
            out.connections.push_back(&conn);
            out.skip_auth = cfg.auto_session_relogon && conn.is_session_logged_on;
        }
        return out;
    }

    /// Sends a subscribe request; on success records the subscription and calls `done` with its
    /// id in `user_data`.
    void subscribe(const std::string& method, const Params& payload,
                   WebsocketMessageSendOptions options, const SubscribeDone& done) {
        if (stopping()) {
            done(std::make_exception_ptr(WebsocketCancelledError()), {}, 0);
            return;
        }
        if (!is_connected()) {
            done(std::make_exception_ptr(WebsocketNotConnectedError()), {}, 0);
            return;
        }
        if (options.is_session_logon || options.is_session_logout) {
            done(std::make_exception_ptr(
                     WebsocketError("A subscription cannot be a session logon / logout")),
                 {}, 0);
            return;
        }
        detail::Connection* conn = nullptr;
        bool skip_auth = false;
        try {
            auto selected = select_targets(options);
            conn = selected.connections.front();
            skip_auth = selected.skip_auth;
        } catch (...) {
            done(std::current_exception(), {}, 0);
            return;
        }
        const detail::Socket* socket = conn->socket.get();
        auto on_response =
            [this, conn, socket, request = detail::SessionLogon{method, payload, options},
             done](std::exception_ptr ep, std::vector<WebsocketApiRawResponse> responses) {
                if (ep) {
                    done(ep, {}, 0);
                    return;
                }
                if (conn->close_initiated) {
                    // disconnect() ran meanwhile: the subscription ends with the connection.
                    done(std::make_exception_ptr(WebsocketCancelledError(true)), {}, 0);
                    return;
                }
                const auto id = ++next_user_data_id;
                auto& entry = user_data[id];
                entry.request = request;
                entry.connection = conn;
                entry.socket = socket;
                entry.subscription_id = subscription_id_of(responses.front().result);
                entry.listeners.buffer_until_first_callback();
                // Answered on a socket that a renewal replaced after the subscriptions were sent
                // again on the new one: send this one there too. (A socket still restoring, or
                // a reconnect, picks it up by itself.)
                if (conn->socket && conn->socket.get() != socket && conn->resubscribed) {
                    resubscribe_one(*conn, id, request);
                }
                done(nullptr, std::move(responses.front()), id);
            };
        try {
            send_on({conn}, method, payload, options, skip_auth, on_response);
        } catch (...) {
            done(std::current_exception(), {}, 0);
        }
    }

    /// One request of those restoring `socket` (see `Connection::restoring`) completed.
    void restored(detail::Connection& conn, const detail::Socket* socket) {
        if (conn.socket.get() != socket || conn.restoring == 0) {
            return;
        }
        --conn.restoring;
        if (conn.restoring == 0) {
            notify();
        }
    }

    /// Sends the subscriptions of `conn` again on its new socket.
    void resubscribe(detail::Connection& conn) {
        conn.resubscribed = true;
        // Collected first: a failure emits an event whose callback may change `user_data`.
        std::vector<std::pair<std::uint64_t, detail::SessionLogon>> pending;
        for (const auto& [id, entry] : user_data) {
            if (entry.request && entry.connection == &conn) {
                pending.emplace_back(id, *entry.request);
            }
        }
        for (const auto& [sub_id, request] : pending) {
            resubscribe_one(conn, sub_id, request);
        }
    }

    /// Sends the subscription `id` again on the current socket of `conn`.
    void resubscribe_one(detail::Connection& conn, std::uint64_t id,
                         const detail::SessionLogon& request) {
        const detail::Socket* socket = conn.socket.get();
        auto fail = [this, &conn](const std::string& why) {
            const auto msg = "WebsocketApi: user data subscription failed on " + conn.id +
                             " after it reopened: " + why;
            Logger::error(msg);
            emit({WebsocketEventType::Error, msg, 0, conn.id});
        };
        ++conn.restoring;
        try {
            send_on({&conn}, request.method, request.payload, request.options,
                    cfg.auto_session_relogon && conn.is_session_logged_on,
                    [this, &conn, id, socket, fail](std::exception_ptr ep,
                                                    std::vector<WebsocketApiRawResponse> res) {
                        // Superseded once the socket is gone: the next one subscribes again.
                        if (stopping() || conn.socket.get() != socket) {
                            return;
                        }
                        if (const auto it = user_data.find(id); it != user_data.end()) {
                            if (ep) {
                                fail(describe(ep));
                            } else {
                                it->second.socket = socket;
                                it->second.subscription_id = subscription_id_of(res.front().result);
                            }
                        } else if (!ep) {
                            // Unsubscribed while this was in flight: end the new one too.
                            if (const auto sub = subscription_id_of(res.front().result)) {
                                send_unsubscribe(conn, *sub);
                            }
                        }
                        restored(conn, socket);
                    });
        } catch (const std::exception& e) {
            fail(e.what());
            restored(conn, socket);
        }
    }

    /// Forgets the subscription `id` and ends it on the server: `userDataStream.unsubscribe` with
    /// its current `subscriptionId`, on the connection that holds it. Nothing is sent when its
    /// socket is gone (the subscription ended with it) or replaced (the old socket takes it when it
    /// closes, and a resubscription still in flight is ended once answered).
    void end_subscription(std::uint64_t id) {
        const auto it = user_data.find(id);
        if (it == user_data.end()) {
            return;
        }
        const bool from_request = it->second.request.has_value();
        auto* conn = it->second.connection;
        const auto* socket = it->second.socket;
        auto subscription_id = std::move(it->second.subscription_id);
        user_data.erase(it);
        if (!from_request || !subscription_id || conn == nullptr || stopping() ||
            conn->close_initiated || conn->socket == nullptr || conn->socket.get() != socket) {
            return;
        }
        send_unsubscribe(*conn, *subscription_id);
    }

    void send_unsubscribe(detail::Connection& conn, const json::value& subscription_id) {
        auto fail = [this, &conn, subscription_id](const std::string& why) {
            const auto msg = "WebsocketApi: ending user data subscription " +
                             json::serialize(subscription_id) + " on " + conn.id +
                             " failed: " + why;
            Logger::warn(msg);
            emit({WebsocketEventType::Error, msg, 0, conn.id});
        };
        try {
            send_on(
                {&conn}, std::string(kUserDataUnsubscribe),
                Params{{"subscriptionId", subscription_id}}, {}, false,
                [this, fail](std::exception_ptr ep, const std::vector<WebsocketApiRawResponse>&) {
                    if (ep && !stopping()) {
                        fail(describe(ep));
                    }
                });
        } catch (const std::exception& e) {
            fail(e.what());
        }
    }

    /// After a `userDataStream.unsubscribe` sent with `send_message`: forgets the subscriptions it
    /// ended on that socket (all of them without a `subscriptionId`), so that reconnects do not
    /// send them again.
    void forget_unsubscribed(const detail::Connection& conn, const detail::Socket* socket,
                             const Params& payload) {
        const auto it = payload.find("subscriptionId");
        const json::value* wanted =
            it == payload.end() || it->second.is_null() ? nullptr : &it->second;
        std::erase_if(user_data, [&](const auto& e) {
            const auto& entry = e.second;
            return entry.request && entry.connection == &conn && entry.socket == socket &&
                   (wanted == nullptr ||
                    (entry.subscription_id && *entry.subscription_id == *wanted));
        });
    }

    [[nodiscard]] static bool receives(const UserData& entry, const detail::Connection& conn,
                                       const detail::Socket& socket,
                                       const json::value* subscription_id) {
        if (entry.connection == nullptr) {
            return true;
        }
        if (entry.connection != &conn || entry.socket != &socket) {
            return false;
        }
        return !entry.subscription_id || subscription_id == nullptr ||
               *entry.subscription_id == *subscription_id;
    }

    WebsocketStreamHandle make_handle(std::string name, std::uint64_t id) {
        const std::weak_ptr<Impl> weak = std::static_pointer_cast<Impl>(shared_from_this());
        auto add = [weak, id](std::shared_ptr<detail::StreamSlot> slot) {
            if (const auto impl = weak.lock()) {
                impl->execute_or_post([impl = impl.get(), id, slot = std::move(slot)]() mutable {
                    if (const auto it = impl->user_data.find(id); it != impl->user_data.end()) {
                        it->second.listeners.add(std::move(slot), impl->gate());
                    }
                });
            }
        };
        auto remove = [weak, id](const std::vector<std::shared_ptr<detail::StreamSlot>>&,
                                 bool /*wait*/) {
            if (const auto impl = weak.lock()) {
                impl->post([impl = impl.get(), id] { impl->end_subscription(id); });
            }
        };
        return {std::move(name),
                std::make_shared<detail::FunctionStreamBinding>(std::move(add), std::move(remove))};
    }

    void send(const std::string& method, const Params& payload, WebsocketMessageSendOptions options,
              std::function<void(std::exception_ptr, std::vector<WebsocketApiRawResponse>)> done,
              std::function<void()>* on_cancel = nullptr) {
        if (stopping()) {
            done(std::make_exception_ptr(WebsocketCancelledError()), {});
            return;
        }
        if (!is_connected()) {
            done(std::make_exception_ptr(WebsocketNotConnectedError()), {});
            return;
        }
        const bool multi = options.is_session_logon || options.is_session_logout;
        Targets selected;
        try {
            selected = select_targets(options);
        } catch (...) {
            done(std::current_exception(), {});
            return;
        }
        auto& targets = selected.connections;
        const bool skip_auth = selected.skip_auth;

        if (method == kUserDataUnsubscribe) {
            done = [this, conn = targets.front(), socket = targets.front()->socket.get(), payload,
                    done = std::move(done)](std::exception_ptr ep,
                                            std::vector<WebsocketApiRawResponse> responses) {
                if (!ep && !stopping()) {
                    forget_unsubscribed(*conn, socket, payload);
                }
                done(ep, std::move(responses));
            };
        }
        if (!multi || !cfg.auto_session_relogon) {
            try {
                send_on(targets, method, payload, options, skip_auth, done, on_cancel);
            } catch (...) {
                done(std::current_exception(), {});
            }
            return;
        }

        // Session logon / logout: record the state on success, for every connection (those
        // reopening log on when they open).
        std::vector<const detail::Socket*> sockets;
        sockets.reserve(targets.size());
        for (const auto* conn : targets) {
            sockets.push_back(conn->socket.get());
        }
        auto on_done = [this, targets, sockets, method, payload, options, done = std::move(done)](
                           std::exception_ptr ep, std::vector<WebsocketApiRawResponse> responses) {
            if (!ep && !stopping()) {
                for (const auto& c : connections) {
                    if (options.is_session_logon) {
                        c->session_logon = detail::SessionLogon{method, payload, options};
                    } else {
                        c->is_session_logged_on = false;
                        c->session_logon.reset();
                    }
                }
                for (std::size_t i = 0; i < targets.size() && options.is_session_logon; ++i) {
                    if (targets[i]->socket.get() == sockets[i]) {
                        targets[i]->is_session_logged_on = true;
                    }
                }
                // The others (answered on a socket that a renewal replaced, or opened meanwhile)
                // log their current socket on.
                for (const auto& c : connections) {
                    if (options.is_session_logon && c->socket && !c->is_session_logged_on &&
                        !c->close_initiated) {
                        logon(*c, false);
                    }
                }
            }
            done(ep, std::move(responses));
        };
        try {
            send_on(targets, method, payload, options, false, on_done, on_cancel);
        } catch (...) {
            on_done(std::current_exception(), {});
        }
    }

    void on_open(detail::Connection& conn) override {
        if (!conn.session_logon || conn.is_session_logged_on) {
            resubscribe(conn);
            return;
        }
        logon(conn, true);
    }

    /// Logs the current socket of `conn` on with the recorded session logon, then sends the
    /// subscriptions again if `then_resubscribe`.
    void logon(detail::Connection& conn, bool then_resubscribe) {
        const auto request = *conn.session_logon;
        const detail::Socket* socket = conn.socket.get();
        Logger::info("WebsocketApi: logging connection " + conn.id + " on again");
        auto fail = [this, &conn](const std::string& why) {
            const auto msg = "WebsocketApi: session re-logon failed on " + conn.id + ": " + why;
            Logger::error(msg);
            emit({WebsocketEventType::Error, msg, 0, conn.id});
        };
        ++conn.restoring;
        try {
            send_on({&conn}, request.method, request.payload, request.options, false,
                    [this, &conn, socket, fail, then_resubscribe](
                        std::exception_ptr ep, const std::vector<WebsocketApiRawResponse>&) {
                        // Superseded once the socket is gone: the next one logs on again.
                        if (stopping() || conn.socket.get() != socket) {
                            return;
                        }
                        if (ep) {
                            fail(describe(ep));
                        } else {
                            conn.is_session_logged_on = true;
                        }
                        if (then_resubscribe) {
                            resubscribe(conn);
                        }
                        restored(conn, socket);
                    });
        } catch (const std::exception& e) {
            fail(e.what());
            if (then_resubscribe) {
                resubscribe(conn);
            }
            restored(conn, socket);
        }
    }

    bool on_message(detail::Connection& conn, const detail::Socket& socket, std::string_view text,
                    bool retired) override {
        json::value msg;
        try {
            msg = parse_json(text);
        } catch (const std::exception& e) {
            Logger::error("WebsocketApi: failed to parse a message: " + std::string(e.what()));
            return true;
        }
        auto* obj = msg.if_object();
        if (obj == nullptr) {
            Logger::warn("WebsocketApi: unexpected message: " + std::string(text));
            return true;
        }
        if (const auto* id = obj->if_contains("id"); id != nullptr && id->is_string()) {
            const std::string key(id->get_string());
            if (!complete_request(conn, key, nullptr, std::move(*obj))) {
                Logger::warn("WebsocketApi: received a response for an unknown or timed-out "
                             "request " +
                             key);
            }
            return true;
        }
        if (auto* event = obj->if_contains("event"); event != nullptr && event->is_object()) {
            const auto* type = event->get_object().if_contains("e");
            if (type == nullptr || !type->is_string()) {
                Logger::warn("WebsocketApi: event without a type: " + std::string(text));
                return true;
            }
            if (type->get_string() == "serverShutdown") {
                if (retired) {
                    // That socket is already replaced.
                    return true;
                }
                Logger::info("WebsocketApi: serverShutdown received on " + conn.id +
                             "; renewing the connection");
                renew(conn);
                return true;
            }
            const auto* subscription_id = obj->if_contains("subscriptionId");
            // Collected first: a callback may add or remove subscriptions.
            std::vector<std::uint64_t> targets;
            for (const auto& [id, entry] : user_data) {
                if (receives(entry, conn, socket, subscription_id)) {
                    targets.push_back(id);
                }
            }
            for (const auto id : targets) {
                if (const auto it = user_data.find(id); it != user_data.end()) {
                    it->second.listeners.deliver(*event, gate());
                }
            }
            return true;
        }
        Logger::warn("WebsocketApi: received a response for an unknown or timed-out request");
        return true;
    }
};

WebsocketApi::WebsocketApi(WebsocketApiConfig configuration, detail::ClientOptions options)
    : impl_(std::make_shared<Impl>(std::move(configuration), std::move(options.user_agent))) {
    impl_->start();
}

WebsocketApi::~WebsocketApi() {
    impl_->stop();
}

const WebsocketApiConfig& WebsocketApi::configuration() const noexcept {
    return impl_->cfg;
}

const SignatureGenerator& WebsocketApi::signature_generator() const noexcept {
    return impl_->signer;
}

asio::any_io_executor WebsocketApi::get_executor() const noexcept {
    return impl_->executor();
}

namespace {

/// Runs `start(complete)` on the strand and completes `handler` on its associated executor.
template <class Signature, class Start>
void initiate(detail::WebsocketCommon& impl, asio::any_completion_handler<Signature> handler,
              Start start) {
    auto handler_ex = asio::prefer(asio::get_associated_executor(handler, impl.executor()),
                                   asio::execution::outstanding_work.tracked);
    asio::dispatch(impl.executor(), [keep = impl.shared_from_this(), handler = std::move(handler),
                                     handler_ex, start = std::move(start)]() mutable {
        auto shared = std::make_shared<asio::any_completion_handler<Signature>>(std::move(handler));
        start([shared, handler_ex](auto... args) {
            asio::dispatch(handler_ex, [shared, ... args = std::move(args)]() mutable {
                if (*shared) {
                    detail::run_handler([&] { std::move (*shared)(std::move(args)...); });
                }
            });
        });
    });
}

} // namespace

void WebsocketApi::start_connect(asio::any_completion_handler<ConnectSignature> handler) {
    Impl* impl = impl_.get();
    initiate(*impl, std::move(handler), [impl](auto complete) {
        std::vector<detail::Connection*> all;
        all.reserve(impl->connections.size());
        for (const auto& conn : impl->connections) {
            all.push_back(conn.get());
        }
        impl->connect_connections(
            all, [impl](detail::Connection& c) { return impl->reconnect_url(c); },
            [complete](std::exception_ptr ep) { complete(ep); });
    });
}

void WebsocketApi::connect() {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("connect", "async_connect");
    }
    async_connect(asio::use_future).get();
}

void WebsocketApi::start_disconnect(asio::any_completion_handler<ConnectSignature> handler) {
    Impl* impl = impl_.get();
    initiate(*impl, std::move(handler), [impl](auto complete) {
        // The server ends the subscriptions with the connections.
        std::erase_if(impl->user_data, [](const auto& e) { return e.second.request.has_value(); });
        impl->disconnect_all([complete](std::exception_ptr ep) { complete(ep); });
    });
}

void WebsocketApi::disconnect() {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("disconnect", "async_disconnect");
    }
    async_disconnect(asio::use_future).get();
}

bool WebsocketApi::is_connected() const {
    return impl_->connected();
}

void WebsocketApi::ping_server() {
    impl_->post([impl = impl_.get()] { impl->ping_server(); });
}

Subscription WebsocketApi::add_event_callback(detail::Callback<WebsocketEvent> callback,
                                              bool with_messages) {
    return impl_->add_event_callback(std::move(callback), with_messages);
}

void WebsocketApi::start_send(std::string method, Params payload,
                              WebsocketMessageSendOptions options,
                              asio::any_completion_handler<SendSignature> handler) {
    Impl* impl = impl_.get();
    auto handler_ex = asio::prefer(asio::get_associated_executor(handler, impl->executor()),
                                   asio::execution::outstanding_work.tracked);

    // One completion, from the response, a failure or a cancellation, whichever comes first.
    // Touched on the strand only.
    struct Op {
        asio::any_completion_handler<SendSignature> handler;
        bool done = false;
        /// Forgets the pending request once the caller has been cancelled.
        std::function<void()> forget;
    };
    auto op = std::make_shared<Op>();
    auto user_slot = asio::get_associated_cancellation_slot(handler);
    op->handler = std::move(handler);

    auto complete = [op, handler_ex, user_slot](std::exception_ptr ep,
                                                std::vector<WebsocketApiRawResponse> res) mutable {
        if (std::exchange(op->done, true)) {
            return;
        }
        op->forget = nullptr;
        asio::dispatch(handler_ex, [op, ep, res = std::move(res), user_slot]() mutable {
            if (user_slot.is_connected()) {
                user_slot.clear();
            }
            detail::run_handler([&] { std::move(op->handler)(ep, std::move(res)); });
        });
    };

    if (user_slot.is_connected()) {
        // The slot may outlive the client, so it holds it only weakly.
        user_slot.assign([weak = std::weak_ptr<Impl>(impl_), op,
                          complete](asio::cancellation_type type) mutable {
            if ((type & (asio::cancellation_type::terminal | asio::cancellation_type::partial |
                         asio::cancellation_type::total)) == asio::cancellation_type::none) {
                return;
            }
            const auto alive = weak.lock();
            if (!alive) {
                return;
            }
            asio::post(alive->executor(), [op, complete]() mutable {
                auto forget = std::move(op->forget);
                complete(std::make_exception_ptr(WebsocketCancelledError(true)), {});
                if (forget) {
                    forget();
                }
            });
        });
    }

    asio::dispatch(impl->executor(), [impl = impl_, method = std::move(method),
                                      payload = std::move(payload), options, op,
                                      complete]() mutable {
        if (op->done) {
            return; // Cancelled before it was sent.
        }
        impl->send(
            method, payload, options,
            [complete](std::exception_ptr ep, std::vector<WebsocketApiRawResponse> res) mutable {
                complete(ep, std::move(res));
            },
            &op->forget);
    });
}

std::vector<WebsocketApiRawResponse>
WebsocketApi::send_message(std::string method, Params payload,
                           WebsocketMessageSendOptions options) {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("send_message", "async_send_message");
    }
    return async_send_message(std::move(method), std::move(payload), options, asio::use_future)
        .get();
}

void WebsocketApi::start_subscribe(std::string method, Params payload,
                                   WebsocketMessageSendOptions options,
                                   asio::any_completion_handler<SubscribeSignature> handler) {
    Impl* impl = impl_.get();
    initiate(*impl, std::move(handler),
             [impl, method = std::move(method), payload = std::move(payload),
              options](auto complete) mutable {
                 impl->subscribe(method, payload, options,
                                 [impl, complete](std::exception_ptr ep,
                                                  WebsocketApiRawResponse response,
                                                  std::uint64_t id) {
                                     WebsocketApiRawSubscription out;
                                     if (!ep) {
                                         const auto& entry = impl->user_data.at(id);
                                         auto name = entry.subscription_id
                                                         ? json::serialize(*entry.subscription_id)
                                                         : detail::random_string();
                                         out.response = std::move(response);
                                         out.stream = impl->make_handle(std::move(name), id);
                                     }
                                     complete(ep, std::move(out));
                                 });
             });
}

WebsocketApiRawSubscription WebsocketApi::subscribe(std::string method, Params payload,
                                                    WebsocketMessageSendOptions options) {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("subscribe", "async_subscribe");
    }
    return async_subscribe(std::move(method), std::move(payload), options, asio::use_future).get();
}

WebsocketStreamHandle WebsocketApi::create_stream(std::string id) {
    if (id.empty()) {
        id = detail::random_string();
    }
    const auto key = ++impl_->next_user_data_id;
    impl_->execute_or_post([impl = impl_.get(), key] {
        impl->user_data[key].listeners.buffer_until_first_callback();
    });
    return impl_->make_handle(std::move(id), key);
}

} // namespace binance::common
