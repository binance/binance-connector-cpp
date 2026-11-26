//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <exception>
#include <functional>
#include <future>
#include <map>
#include <mutex>
#include <set>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/prefer.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/json/serialize.hpp>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/logger.hpp>
#include <binance/common/signer.hpp>
#include <binance/common/websocket_streams.hpp>

#include "testing.hpp"
#include "utils.hpp"
#include "websocket_common.hpp"

namespace binance::common {

namespace asio = boost::asio;
namespace json = boost::json;

namespace {

/// An empty URL path means none.
std::optional<std::string> non_empty(const std::optional<std::string>& url_path) {
    return url_path && !url_path->empty() ? url_path : std::nullopt;
}

const std::string& require_url(const std::optional<std::string>& url) {
    if (!url || url->empty()) {
        throw ConfigError("Configuration missing or invalid `url`");
    }
    return *url;
}

/// Signed streams need the API key and a way to sign.
void require_credentials(const WebsocketStreamsConfig& cfg) {
    if (!cfg.api_key || cfg.api_key->empty()) {
        throw ConfigError("'api_key' is required for signed websocket streams");
    }
    if (!cfg.api_secret && !cfg.private_key) {
        throw ConfigError(
            "Either 'api_secret' or 'private_key' must be provided for signed websocket streams");
    }
}

detail::WebsocketSettings settings_for(const WebsocketStreamsConfig& cfg,
                                       const detail::ClientOptions& options) {
    detail::WebsocketSettings s;
    if (options.signed_streams) {
        require_credentials(cfg);
        s.headers.emplace_back("X-MBX-APIKEY", *cfg.api_key);
    }
    s.name = "WebsocketStreams";
    s.reconnect_delay = cfg.reconnect_delay;
    s.connect_timeout = cfg.connect_timeout;
    s.compression = cfg.compression;
    s.max_message_size = cfg.max_message_size;
    s.is_pool = cfg.mode.is_pool();
    s.proxy = cfg.proxy;
    s.proxy_from_env = cfg.proxy_from_env;
    s.agent = cfg.agent;
    s.transport = cfg.transport;
    s.user_agent = detail::user_agent_or_default(options.user_agent);
    s.executor = cfg.executor;
    return s;
}

/// Binance serves at most this many streams per connection.
constexpr std::size_t kMaxStreamsPerConnection = 1024;
/// Longest connection URL, well within common request header limits (often 8 KB): the streams
/// beyond it are subscribed once the connection opens.
constexpr std::size_t kMaxUrlLength = 4096;
/// Signed streams are valid for this long after their timestamp.
constexpr int kSignedRecvWindow = 30000;
/// Signed streams expect a PING this often.
constexpr std::chrono::milliseconds kSignedPingInterval{30000};
std::atomic<std::chrono::milliseconds::rep> signed_ping_interval_override{0};

std::chrono::milliseconds signed_ping_interval() noexcept {
    const auto ms = signed_ping_interval_override.load();
    return ms > 0 ? std::chrono::milliseconds(ms) : kSignedPingInterval;
}

std::size_t connection_count(const WebsocketStreamsConfig& cfg,
                             const std::vector<std::string>& url_paths) {
    return cfg.mode.pool_size() * std::max<std::size_t>(1, url_paths.size());
}

} // namespace

struct WebsocketStreams::Impl final : detail::WebsocketCommon {
    using Clock = std::chrono::steady_clock;

    Impl(WebsocketStreamsConfig configuration, std::vector<std::string> paths,
         const detail::ClientOptions& options)
        : WebsocketCommon(settings_for(configuration, options), require_url(configuration.url),
                          connection_count(configuration, paths)),
          cfg(std::move(configuration)), signed_streams(options.signed_streams),
          strictly_number(options.stream_id_is_strictly_number),
          signer(cfg.api_secret, cfg.private_key, cfg.private_key_passphrase),
          url_paths(std::move(paths)) {
        if (signed_streams) {
            signer.load_key();
        }
        // The signer keeps what it needs, so the passphrase is not kept in the configuration.
        cfg.private_key_passphrase.reset();
        const auto pool = cfg.mode.pool_size();
        for (std::size_t i = 0; i < url_paths.size(); ++i) {
            for (std::size_t j = 0; j < pool; ++j) {
                connections[(i * pool) + j]->url_path = url_paths[i];
            }
        }
    }

    struct MappedStream {
        std::string stream;
        detail::Connection* connection = nullptr;
    };

    /// A SUBSCRIBE or UNSUBSCRIBE, sent at the end of the strand turn.
    struct Frame {
        detail::Connection* conn = nullptr;
        /// The socket it is for: dropped if the connection has another one by then.
        const detail::Socket* socket = nullptr;
        std::string method;
        std::vector<std::string> streams;
        /// The caller's id, if any: such a frame is not merged with others.
        std::optional<json::value> id;
        bool strictly_number = false;
    };

    /// A SUBSCRIBE or UNSUBSCRIBE waiting for its response.
    struct Request {
        std::string method;
        std::vector<std::string> streams;
        /// Counted in `Connection::restoring` for this socket: a renewal keeps the previous
        /// socket until it is answered.
        const detail::Socket* restoring = nullptr;
        /// The socket it went out on: the acknowledgement of a signed command, which has no id,
        /// is matched with the oldest command of its kind sent on the same socket.
        const detail::Socket* socket = nullptr;
    };

    /// An `async_wait_subscribed` call, which its cancellation slot may end before the server
    /// answers.
    struct WaitTicket {
        std::atomic<bool> cancelled{false};
        /// Set on the strand once the wait is queued.
        std::uint64_t id = 0;
    };

    /// A renewed connection's previous socket still delivers the streams that the new one has
    /// not delivered yet, until `until` (it closes by then).
    struct Handover {
        std::set<std::string> started;
        Clock::time_point until;
    };

    using Assignment = std::vector<std::pair<detail::Connection*, std::vector<std::string>>>;

    WebsocketStreamsConfig cfg;
    /// The product's streams are signed (`ClientOptions::signed_streams`).
    const bool signed_streams;
    /// SUBSCRIBE / UNSUBSCRIBE ids are always numbers.
    const bool strictly_number;
    SignatureGenerator signer;
    std::vector<std::string> url_paths;
    /// Stream key → the connection carrying it.
    std::map<std::string, MappedStream> connection_streams;
    /// Connection → the number of streams mapped to it.
    std::map<const detail::Connection*, std::size_t> stream_counts;
    /// Stream key → callbacks.
    std::map<std::string, detail::StreamListeners> listeners;
    std::vector<Frame> outgoing;
    bool flush_posted = false;
    /// Connection → requests by serialized id, oldest first.
    std::map<const detail::Connection*, std::multimap<std::string, Request>> requests;
    std::map<const detail::Connection*, Handover> handovers;
    std::size_t round_robin = 0;

    using Waiter = std::function<void(std::exception_ptr)>;
    /// Stream key → the `async_wait_subscribed` calls waiting for its acknowledgement, by id.
    std::map<std::string, std::vector<std::pair<std::uint64_t, Waiter>>> waiters;
    std::uint64_t next_waiter = 0;
    /// The keys whose subscription the server acknowledged.
    std::set<std::string> confirmed;
    /// Key → the rejection of its last SUBSCRIBE, for a wait that starts after it arrived.
    std::map<std::string, std::exception_ptr> rejections;
    /// Connection → the streams in the URL it is opening with: acknowledged once it opens.
    std::map<const detail::Connection*, std::vector<std::string>> url_streams;

    // What callers see, updated by their calls on any thread, so that no call has to wait for
    // the executor.
    mutable std::mutex state_mutex;
    /// The keys of the streams subscribed or queued.
    std::set<std::string> subscribed;
    /// Stream key → live handles: the stream stays subscribed while one exists, even without a
    /// callback yet.
    std::map<std::string, std::size_t> handles;
    /// Bumped by `disconnect()`: the handles created before it no longer do anything.
    std::uint64_t epoch = 0;

    static void check_streams(const std::vector<std::string>& streams) {
        if (std::any_of(streams.begin(), streams.end(), [](const auto& s) { return s.empty(); })) {
            throw WebsocketError("WebsocketStreams: empty stream name");
        }
    }

    /// Throws for a URL path that no connection serves.
    void check_url_path(const std::optional<std::string>& url_path) const {
        if (url_path &&
            std::find(url_paths.begin(), url_paths.end(), *url_path) == url_paths.end()) {
            throw WebsocketError("WebsocketStreams: unknown URL path '" + *url_path + "'");
        }
    }

    [[nodiscard]] std::optional<json::value> request_id(const std::optional<StreamId>& id) const {
        // Signed commands have no id.
        if (!id || signed_streams) {
            return std::nullopt;
        }
        return detail::normalize_stream_id(id, strictly_number);
    }

    // ---- Any thread ----

    void mark_subscribed(const std::vector<std::string>& streams,
                         const std::optional<std::string>& url_path) {
        const std::lock_guard lock(state_mutex);
        for (const auto& s : streams) {
            subscribed.insert(stream_key(s, url_path));
        }
    }

    /// The streams of `connect()`, on every URL path.
    void mark_connect_streams(const std::vector<std::string>& streams) {
        if (url_paths.empty()) {
            mark_subscribed(streams, std::nullopt);
        }
        for (const auto& path : url_paths) {
            mark_subscribed(streams, path);
        }
    }

    /// `unsubscribe()` leaves the streams that a handle uses.
    void mark_unsubscribed(const std::vector<std::string>& streams,
                           const std::optional<std::string>& url_path) {
        const std::lock_guard lock(state_mutex);
        for (const auto& s : streams) {
            const auto key = stream_key(s, url_path);
            if (!handles.contains(key)) {
                subscribed.erase(key);
            }
        }
    }

    /// Returns the epoch of the new handle.
    std::uint64_t add_handle(const std::string& key) {
        const std::lock_guard lock(state_mutex);
        ++handles[key];
        subscribed.insert(key);
        return epoch;
    }

    /// False for a handle created before the last `disconnect()`.
    bool remove_handle(const std::string& key, std::uint64_t handle_epoch) {
        const std::lock_guard lock(state_mutex);
        if (handle_epoch != epoch) {
            return false;
        }
        if (const auto h = handles.find(key); h != handles.end() && --h->second == 0) {
            handles.erase(h);
            subscribed.erase(key);
        }
        return true;
    }

    [[nodiscard]] bool is_current(std::uint64_t handle_epoch) const {
        const std::lock_guard lock(state_mutex);
        return handle_epoch == epoch;
    }

    [[nodiscard]] bool has_handle(const std::string& key) const {
        const std::lock_guard lock(state_mutex);
        return handles.contains(key);
    }

    void forget(const std::string& key) {
        const std::lock_guard lock(state_mutex);
        subscribed.erase(key);
    }

    /// `disconnect()`: no stream, and every handle stale.
    void reset_state() {
        const std::lock_guard lock(state_mutex);
        subscribed.clear();
        handles.clear();
        ++epoch;
    }

    [[nodiscard]] bool is_subscribed_key(const std::string& key) const {
        const std::lock_guard lock(state_mutex);
        return subscribed.contains(key);
    }

    [[nodiscard]] bool is_subscribed(const std::string& stream) const {
        const auto suffix = "::" + stream;
        const std::lock_guard lock(state_mutex);
        return std::any_of(subscribed.begin(), subscribed.end(),
                           [&](const auto& key) { return key == stream || key.ends_with(suffix); });
    }

    // ---- Strand ----

    // A completion may run here, inline, and call the client again: the callers fire these after
    // they are done with the maps.

    void finish_waiters(const std::string& key, const std::exception_ptr& ep) {
        const auto it = waiters.find(key);
        if (it == waiters.end()) {
            return;
        }
        auto list = std::move(it->second);
        waiters.erase(it);
        for (auto& [id, waiter] : list) {
            waiter(ep);
        }
    }

    /// The cancellation slot of a wait fired: it ends now, unless it already did.
    void cancel_waiter(const std::string& key, const WaitTicket& ticket) {
        const auto it = waiters.find(key);
        if (it == waiters.end() || ticket.id == 0) {
            return;
        }
        auto& list = it->second;
        const auto entry = std::find_if(list.begin(), list.end(),
                                        [&](const auto& w) { return w.first == ticket.id; });
        if (entry == list.end()) {
            return;
        }
        auto waiter = std::move(entry->second);
        list.erase(entry);
        if (list.empty()) {
            waiters.erase(it);
        }
        waiter(std::make_exception_ptr(WebsocketCancelledError()));
    }

    void confirm(const std::vector<std::string>& keys) {
        for (const auto& key : keys) {
            confirmed.insert(key);
            rejections.erase(key);
        }
        for (const auto& key : keys) {
            finish_waiters(key, nullptr);
        }
    }

    /// The subscriptions of `keys` ended (rejected, unsubscribed): their waits fail with `ep`.
    void unconfirm(const std::vector<std::string>& keys, const std::exception_ptr& ep) {
        for (const auto& key : keys) {
            confirmed.erase(key);
        }
        for (const auto& key : keys) {
            finish_waiters(key, ep);
        }
    }

    /// `disconnect()` or destruction: every wait is cancelled.
    void cancel_waiters() {
        confirmed.clear();
        rejections.clear();
        url_streams.clear();
        const auto cancelled = std::make_exception_ptr(WebsocketCancelledError());
        for (auto& [key, list] : std::exchange(waiters, {})) {
            for (auto& [id, waiter] : list) {
                waiter(cancelled);
            }
        }
    }

    void wait_subscribed(const std::string& key, Waiter done, WaitTicket& ticket) {
        if (!stopping() && !ticket.cancelled) {
            if (confirmed.contains(key)) {
                done(nullptr);
                return;
            }
            if (is_subscribed_key(key)) {
                ticket.id = ++next_waiter;
                waiters[key].emplace_back(ticket.id, std::move(done));
                return;
            }
            if (const auto it = rejections.find(key); it != rejections.end()) {
                done(it->second);
                return;
            }
        }
        done(std::make_exception_ptr(WebsocketCancelledError()));
    }

    void on_shutdown() override { cancel_waiters(); }

    [[nodiscard]] static bool sendable(const detail::Connection& conn) {
        return conn.socket && !conn.close_initiated;
    }

    [[nodiscard]] static bool reconnecting(const detail::Connection& conn) {
        return conn.reconnection_pending && !conn.close_initiated && !conn.failed;
    }

    /// 0: ready, 1: reconnecting, 2: closed or failed.
    [[nodiscard]] static int rank(const detail::Connection& conn) {
        if (is_connection_ready(conn, true)) {
            return 0;
        }
        return reconnecting(conn) ? 1 : 2;
    }

    [[nodiscard]] std::size_t stream_count(const detail::Connection* conn) const {
        const auto it = stream_counts.find(conn);
        return it == stream_counts.end() ? 0 : it->second;
    }

    void map_stream(const std::string& key, std::string stream, detail::Connection* conn) {
        auto& mapped = connection_streams[key];
        if (mapped.connection != nullptr) {
            --stream_counts[mapped.connection];
        }
        mapped = {std::move(stream), conn};
        ++stream_counts[conn];
    }

    void unmap_stream(std::map<std::string, MappedStream>::iterator it) {
        --stream_counts[it->second.connection];
        connection_streams.erase(it);
    }

    /// Round-robin over `candidates`, preferring those below the per-connection limit.
    detail::Connection* pick_from(const std::vector<detail::Connection*>& candidates) {
        std::vector<detail::Connection*> roomy;
        std::copy_if(candidates.begin(), candidates.end(), std::back_inserter(roomy),
                     [this](const auto* c) { return stream_count(c) < kMaxStreamsPerConnection; });
        const auto& from = roomy.empty() ? candidates : roomy;
        return from.empty() ? nullptr : from[round_robin++ % from.size()];
    }

    /// The connection for a stream of `url_path`, other than `exclude`: a ready one (open ones
    /// first with `prefer_open`), else a reconnecting one, else, with `allow_closed`, a closed or
    /// failed one, which gets the stream once `connect()` opens it. In single mode without a URL
    /// path: the only connection.
    detail::Connection* pick_connection(const std::optional<std::string>& url_path,
                                        const detail::Connection* exclude, bool prefer_open,
                                        bool allow_closed) {
        if (!settings().is_pool && !url_path) {
            auto* only = connections.front().get();
            return only == exclude ? nullptr : only;
        }
        std::vector<detail::Connection*> serving;
        for (const auto& c : connections) {
            if (c.get() != exclude && (!url_path || c->url_path == url_path)) {
                serving.push_back(c.get());
            }
        }
        const auto pick = [&](auto pred) {
            std::vector<detail::Connection*> out;
            std::copy_if(serving.begin(), serving.end(), std::back_inserter(out), pred);
            return pick_from(out);
        };
        detail::Connection* conn = nullptr;
        if (prefer_open) {
            conn = pick([](const auto* c) { return is_connection_ready(*c, false); });
        }
        if (conn == nullptr) {
            conn = pick([](const auto* c) { return is_connection_ready(*c, true); });
        }
        if (conn == nullptr) {
            conn = pick([](const auto* c) { return reconnecting(*c); });
        }
        if (conn == nullptr && allow_closed) {
            conn = pick([](const auto* c) { return !c->failed; });
        }
        if (conn == nullptr && allow_closed) {
            conn = pick([](const auto*) { return true; });
        }
        return conn;
    }

    [[nodiscard]] std::string prepare_url(const std::vector<std::string>& streams,
                                          const std::optional<std::string>& url_path) const {
        std::string url = *cfg.url;
        if (url_path) {
            url += "/" + *url_path;
        }
        url += "/stream?streams=";
        for (std::size_t i = 0; i < streams.size(); ++i) {
            if (i != 0) {
                url += '/';
            }
            url += streams[i];
        }
        if (cfg.time_unit) {
            url += "&timeUnit=" + std::string(to_lower_string(*cfg.time_unit));
        }
        return url;
    }

    /// The URL of a signed connection: no streams (`on_open` subscribes them all), and a signature
    /// that is valid now.
    [[nodiscard]] std::string signed_url() const {
        auto query = "random=" + detail::random_string() +
                     "&recvWindow=" + std::to_string(kSignedRecvWindow) +
                     "&timestamp=" + std::to_string(detail::timestamp_ms(cfg.timestamp_provider));
        std::string signature;
        try {
            signature = signer.sign_payload(query);
        } catch (const std::exception& e) {
            // The server rejects the URL, and the connection retries.
            Logger::error("WebsocketStreams: failed to sign the URL: " + std::string(e.what()));
        }
        query += "&signature=" + detail::form_urlencode(signature);
        return *cfg.url + (cfg.url->find('?') == std::string::npos ? '?' : '&') + query;
    }

    /// Every stream mapped to `conn`: in the URL while it stays within `kMaxUrlLength` and the
    /// per-connection limit, the rest by SUBSCRIBE once the socket opens. The queued SUBSCRIBE /
    /// UNSUBSCRIBE are replaced (changes made while the connection opens are sent by `on_open`).
    std::string reconnect_url(detail::Connection& conn) override {
        conn.pending_subscriptions.clear();
        conn.pending_unsubscriptions.clear();
        if (signed_streams) {
            return signed_url();
        }
        std::vector<std::string> streams;
        auto length = prepare_url({}, conn.url_path).size();
        for (const auto& [key, mapped] : connection_streams) {
            if (mapped.connection != &conn) {
                continue;
            }
            if (streams.size() < kMaxStreamsPerConnection &&
                length + mapped.stream.size() + 1 <= kMaxUrlLength) {
                length += mapped.stream.size() + 1;
                streams.push_back(mapped.stream);
            } else {
                conn.pending_subscriptions.push_back(mapped.stream);
            }
        }
        if (!conn.pending_subscriptions.empty()) {
            Logger::info("WebsocketStreams: " + std::to_string(conn.pending_subscriptions.size()) +
                         " streams do not fit in the URL of connection " + conn.id +
                         "; subscribing them once it opens");
        }
        url_streams[&conn] = streams;
        return prepare_url(streams, conn.url_path);
    }

    void send_frame(detail::Connection& conn, const std::string& method,
                    std::vector<std::string> streams, json::value id, bool restoring = false) {
        json::object msg;
        if (signed_streams) {
            std::string value;
            for (const auto& s : streams) {
                value += (value.empty() ? "" : "|") + s;
            }
            msg["command"] = method;
            msg["value"] = value;
        } else {
            msg["method"] = method;
            json::array params;
            for (const auto& s : streams) {
                params.emplace_back(s);
            }
            msg["params"] = std::move(params);
            msg["id"] = id;
        }
        const auto text = json::serialize(msg);
        Logger::debug("WebsocketStreams: " + text);
        send_text(conn, text);
        const detail::Socket* restored = nullptr;
        if (restoring) {
            restored = conn.socket.get();
            ++conn.restoring;
        }
        // The acknowledgement of a signed command carries its sub-type instead of an id: the
        // commands of a kind are answered in order (a multimap keeps equal keys in insertion
        // order).
        requests[&conn].emplace(signed_streams ? method : json::serialize(id),
                                Request{method, std::move(streams), restored, conn.socket.get()});
    }

    /// Queues a SUBSCRIBE / UNSUBSCRIBE for the open socket of `conn`. Those made during one
    /// strand turn go out together, one frame per connection and method where the order allows.
    void queue_frame(detail::Connection& conn, const char* method,
                     const std::vector<std::string>& streams,
                     const std::optional<json::value>& id) {
        if (streams.empty()) {
            return;
        }
        const bool strictly = strictly_number;
        const auto* socket = conn.socket.get();
        const auto last = std::find_if(outgoing.rbegin(), outgoing.rend(),
                                       [&conn](const Frame& f) { return f.conn == &conn; });
        if (!id && last != outgoing.rend() && last->method == method && !last->id &&
            last->strictly_number == strictly && last->socket == socket) {
            last->streams.insert(last->streams.end(), streams.begin(), streams.end());
        } else {
            outgoing.push_back({&conn, socket, method, streams, id, strictly});
        }
        if (!std::exchange(flush_posted, true)) {
            post([this] { flush(); });
        }
    }

    void flush() {
        flush_posted = false;
        for (auto& f : std::exchange(outgoing, {})) {
            if (f.method == "SUBSCRIBE") {
                // Streams the server rejected meanwhile (a signed command answers for streams
                // still queued here) are not subscribed again.
                std::erase_if(f.streams, [&](const std::string& s) {
                    return route(*f.conn, s) == nullptr &&
                           (rejections.contains(stream_key(s, f.conn->url_path)) ||
                            rejections.contains(s));
                });
                if (f.streams.empty()) {
                    continue;
                }
            }
            // Otherwise the connection lost the socket meanwhile, and its URL subscribes again.
            if (!stopping() && sendable(*f.conn) && f.conn->socket.get() == f.socket) {
                send_frame(*f.conn, f.method, std::move(f.streams),
                           f.id ? *f.id
                                : detail::normalize_stream_id(std::nullopt, f.strictly_number));
            }
        }
    }

    void connect(const std::vector<std::string>& streams,
                 std::function<void(std::exception_ptr)> done) {
        // The streams go into the URL of the first connection of each URL path, up to the
        // per-connection limit. A connection that is open or opening gets them by SUBSCRIBE; one
        // being closed by `disconnect()` opens again with them in its URL.
        const auto pool = cfg.mode.pool_size();
        const auto groups = std::max<std::size_t>(1, url_paths.size());
        for (std::size_t g = 0; g < groups; ++g) {
            auto& first = *connections[g * pool];
            std::vector<std::string> fresh;
            for (const auto& s : streams) {
                if (!connection_streams.contains(stream_key(s, first.url_path)) &&
                    std::find(fresh.begin(), fresh.end(), s) == fresh.end()) {
                    fresh.push_back(s);
                }
            }
            if (fresh.empty()) {
                continue;
            }
            if (!first.close_initiated && (first.socket || first.connecting)) {
                subscribe(fresh, std::nullopt, first.url_path, false);
                continue;
            }
            std::vector<std::string> spill;
            for (auto& s : fresh) {
                if (stream_count(&first) < kMaxStreamsPerConnection) {
                    const auto key = stream_key(s, first.url_path);
                    map_stream(key, std::move(s), &first);
                } else {
                    spill.push_back(std::move(s));
                }
            }
            if (!spill.empty()) {
                subscribe(spill, std::nullopt, first.url_path, false);
            }
        }

        std::vector<detail::Connection*> all;
        all.reserve(connections.size());
        for (const auto& conn : connections) {
            all.push_back(conn.get());
        }
        connect_connections(
            all, [this](detail::Connection& c) { return reconnect_url(c); }, std::move(done));
    }

    /// `disconnect()`, on the strand.
    void clear() {
        listeners.clear();
        connection_streams.clear();
        stream_counts.clear();
        outgoing.clear();
        requests.clear();
        handovers.clear();
        for (const auto& conn : connections) {
            conn->pending_subscriptions.clear();
            conn->pending_unsubscriptions.clear();
        }
        cancel_waiters();
    }

    /// SUBSCRIBE on an open connection; on one being opened, queued for `on_open` as well,
    /// unless the stream is in its URL already. A connection that is not open gets its streams
    /// through the URL it opens with.
    void send_or_queue(detail::Connection& conn, const std::vector<std::string>& streams,
                       const std::optional<json::value>& id) {
        if (conn.connecting || conn.renewal_pending) {
            for (const auto& s : streams) {
                if (std::erase(conn.pending_unsubscriptions, s) == 0) {
                    conn.pending_subscriptions.push_back(s);
                }
            }
            Logger::info("WebsocketStreams: connection " + conn.id +
                         " is opening; queueing the subscription");
        }
        if (sendable(conn)) {
            queue_frame(conn, "SUBSCRIBE", streams, id);
        }
    }

    /// `stream` no longer goes to `conn`: drops its queued SUBSCRIBE, or, if it is in the URL of
    /// the socket being opened, UNSUBSCRIBEs once that opens.
    void leave(detail::Connection& conn, const std::string& stream) const {
        if (std::erase(conn.pending_subscriptions, stream) == 0 && conn.connecting &&
            !signed_streams &&
            std::find(conn.pending_unsubscriptions.begin(), conn.pending_unsubscriptions.end(),
                      stream) == conn.pending_unsubscriptions.end()) {
            conn.pending_unsubscriptions.push_back(stream);
        }
    }

    static void assign(Assignment& groups, detail::Connection* conn, const std::string& stream) {
        auto it = std::find_if(groups.begin(), groups.end(),
                               [conn](const auto& g) { return g.first == conn; });
        if (it == groups.end()) {
            groups.emplace_back(conn, std::vector<std::string>{});
            it = std::prev(groups.end());
        }
        it->second.push_back(stream);
    }

    void subscribe(const std::vector<std::string>& streams, const std::optional<json::value>& id,
                   const std::optional<std::string>& url_path, bool buffer) {
        Assignment groups;
        for (const auto& s : streams) {
            const auto key = stream_key(s, url_path);
            rejections.erase(key);
            detail::Connection* conn = nullptr;
            if (const auto it = connection_streams.find(key); it != connection_streams.end()) {
                auto* current = it->second.connection;
                // A stream left on a reconnecting, closed or failed connection moves to a better
                // one.
                if (const auto r = rank(*current); r != 0) {
                    conn = pick_connection(url_path, current, false, false);
                    if (conn != nullptr && rank(*conn) >= r) {
                        conn = nullptr;
                    }
                }
                if (conn == nullptr) {
                    // Debug only: user-data stream names are listen keys.
                    Logger::debug("WebsocketStreams: already subscribed to " + key);
                } else {
                    leave(*current, s);
                }
            } else {
                conn = pick_connection(url_path, nullptr, false, true);
                if (conn == nullptr) {
                    Logger::warn("WebsocketStreams: no connection available to subscribe");
                    Logger::debug("WebsocketStreams: no connection available for " + key);
                }
            }
            if (conn != nullptr) {
                map_stream(key, s, conn);
                assign(groups, conn, s);
            }
            if (buffer && connection_streams.contains(key)) {
                listeners[key].buffer_until_first_callback();
            }
        }
        for (auto& [conn, list] : groups) {
            send_or_queue(*conn, list, id);
        }
    }

    void unsubscribe(const std::vector<std::string>& streams, const std::optional<json::value>& id,
                     const std::optional<std::string>& url_path) {
        Assignment groups;
        std::vector<std::string> gone;
        for (const auto& s : streams) {
            const auto key = stream_key(s, url_path);
            if (has_handle(key)) {
                continue;
            }
            rejections.erase(key);
            listeners.erase(key);
            const auto mapped = connection_streams.find(key);
            if (mapped == connection_streams.end()) {
                Logger::debug("WebsocketStreams: stream " + key +
                              " is not associated with a connection");
                continue;
            }
            auto& conn = *mapped->second.connection;
            if (sendable(conn)) {
                assign(groups, &conn, s);
            }
            leave(conn, s);
            unmap_stream(mapped);
            gone.push_back(key);
        }
        for (auto& [conn, list] : groups) {
            queue_frame(*conn, "UNSUBSCRIBE", list, id);
        }
        unconfirm(gone, std::make_exception_ptr(WebsocketCancelledError()));
    }

    void on_open(detail::Connection& conn) override {
        const bool renewal = !conn.retired.empty();
        if (renewal) {
            handovers[&conn] = {{}, Clock::now() + 2 * kDrainTimeout};
            // Only the previous sockets still answer.
            if (const auto pending = requests.find(&conn); pending != requests.end()) {
                std::erase_if(pending->second, [&](const auto& entry) {
                    const auto* socket = entry.second.socket;
                    return socket != nullptr && socket != conn.socket.get() &&
                           std::none_of(conn.retired.begin(), conn.retired.end(),
                                        [&](const auto& r) { return r.get() == socket; });
                });
            }
        } else {
            // The previous socket is gone, with the responses it owed.
            requests.erase(&conn);
            handovers.erase(&conn);
        }
        if (const auto it = url_streams.find(&conn); it != url_streams.end()) {
            const auto streams = std::move(it->second);
            url_streams.erase(it);
            std::vector<std::string> keys;
            for (const auto& s : streams) {
                if (const auto* key = route(conn, s)) {
                    keys.push_back(*key);
                }
            }
            confirm(keys);
        }
        const auto id = [this] { return detail::normalize_stream_id({}, strictly_number); };
        if (signed_streams) {
            // The URL has no streams: every stream of the connection is subscribed again.
            conn.pending_subscriptions.clear();
            conn.pending_unsubscriptions.clear();
            std::vector<std::string> streams;
            for (const auto& [key, mapped] : connection_streams) {
                if (mapped.connection == &conn) {
                    streams.push_back(mapped.stream);
                }
            }
            if (!streams.empty()) {
                send_frame(conn, "SUBSCRIBE", std::move(streams), id(), renewal);
            }
            keep_alive(conn, signed_ping_interval());
            return;
        }
        if (!conn.pending_subscriptions.empty()) {
            // The previous socket of a renewal serves these streams until this is answered.
            send_frame(conn, "SUBSCRIBE", std::exchange(conn.pending_subscriptions, {}), id(),
                       renewal);
        }
        if (!conn.pending_unsubscriptions.empty()) {
            send_frame(conn, "UNSUBSCRIBE", std::exchange(conn.pending_unsubscriptions, {}), id());
        }
    }

    /// Moves the streams of a connection that will not reconnect to others serving the same
    /// URL path, preferring open ones. Without one ready or reconnecting, they stay until
    /// `connect()`.
    void on_connection_failed(detail::Connection& failed) override {
        requests.erase(&failed);
        handovers.erase(&failed);
        Assignment groups;
        for (auto& [key, mapped] : connection_streams) {
            if (mapped.connection != &failed) {
                continue;
            }
            // Moved or stranded, the stream waits for a new acknowledgement.
            confirmed.erase(key);
            const auto path = key == mapped.stream ? std::nullopt : failed.url_path;
            auto* conn = pick_connection(path, &failed, true, false);
            if (conn == nullptr) {
                Logger::warn("WebsocketStreams: no connection left for a stream of " + failed.id);
                Logger::debug("WebsocketStreams: no connection left for " + key);
                continue;
            }
            --stream_counts[&failed];
            ++stream_counts[conn];
            mapped.connection = conn;
            assign(groups, conn, mapped.stream);
        }
        for (auto& [conn, list] : groups) {
            send_or_queue(*conn, list, std::nullopt);
        }
    }

    /// The key of `stream` if `conn` carries it, else null.
    [[nodiscard]] const std::string* route(const detail::Connection& conn,
                                           const std::string& stream) const {
        auto it = connection_streams.find(stream_key(stream, conn.url_path));
        if ((it == connection_streams.end() || it->second.connection != &conn) && conn.url_path) {
            // Subscribed without a URL path on a connection that has one.
            it = connection_streams.find(stream);
        }
        if (it == connection_streams.end() || it->second.connection != &conn) {
            return nullptr;
        }
        return &it->first;
    }

    /// Whether the previous socket of a renewed `conn` still delivers `stream`.
    [[nodiscard]] bool hands_over(const detail::Connection& conn, const std::string& stream) const {
        const auto it = handovers.find(&conn);
        return it != handovers.end() && Clock::now() < it->second.until &&
               !it->second.started.contains(stream);
    }

    static std::optional<std::string> error_of(const json::object& response) {
        if (const auto* error = response.if_contains("error");
            error != nullptr && !error->is_null()) {
            if (const auto* obj = error->if_object()) {
                if (const auto* msg = obj->if_contains("msg"); msg != nullptr && msg->is_string()) {
                    return std::string(msg->get_string());
                }
            }
            return json::serialize(*error);
        }
        if (response.contains("code") && !response.contains("result")) {
            if (const auto* msg = response.if_contains("msg"); msg != nullptr && msg->is_string()) {
                return std::string(msg->get_string());
            }
            return json::serialize(response);
        }
        return std::nullopt;
    }

    /// Binance's error code in a response, or 0.
    static std::int64_t error_code(const json::object& response) {
        const auto* error = response.if_contains("error");
        const auto* obj = error != nullptr ? error->if_object() : nullptr;
        const auto* code = obj != nullptr ? obj->if_contains("code") : response.if_contains("code");
        return code != nullptr && code->is_int64() ? code->get_int64() : 0;
    }

    void settle(detail::Connection& conn, const Request& request) {
        if (request.restoring != nullptr && request.restoring == conn.socket.get() &&
            conn.restoring > 0) {
            --conn.restoring;
            notify();
        }
    }

    /// The acknowledgement of a signed command. It has no id: it answers the oldest command of
    /// its kind sent on the same socket, and settles only that command's streams. A failure is
    /// reported, whichever socket it came on.
    void on_command(detail::Connection& conn, const detail::Socket& socket, const json::object& msg,
                    bool retired) {
        const auto* sub_type = msg.if_contains("subType");
        const std::string name = sub_type != nullptr && sub_type->is_string()
                                     ? std::string(sub_type->get_string())
                                     : std::string();
        std::optional<Request> request;
        if (const auto pending = requests.find(&conn); pending != requests.end()) {
            const auto [first, last] = pending->second.equal_range(name);
            const auto it = std::find_if(
                first, last, [&](const auto& entry) { return entry.second.socket == &socket; });
            if (it != last) {
                request = std::move(it->second);
                pending->second.erase(it);
                settle(conn, *request);
            }
        }
        const auto* result = msg.if_contains("data");
        const bool ok =
            result != nullptr && result->is_string() && result->get_string() == "SUCCESS";
        // A previous socket's command was sent again on the current one, which answers for it.
        std::vector<std::string> keys;
        if (name == "SUBSCRIBE" && request && !retired) {
            for (const auto& s : request->streams) {
                if (const auto* key = route(conn, s)) {
                    keys.push_back(*key);
                }
            }
        }
        if (ok) {
            Logger::debug("WebsocketStreams: " + name + " succeeded on connection " + conn.id);
            confirm(keys);
            return;
        }
        const auto payload = json::serialize(msg);
        Logger::warn("WebsocketStreams: " + name + " failed on connection " + conn.id + ": " +
                     payload);
        const auto rejection =
            std::make_exception_ptr(WebsocketResponseError(0, name + " failed: " + payload));
        // As for a rejected SUBSCRIBE response: the streams it was for are dropped, before the
        // Error event, whose callbacks see them gone.
        for (const auto& key : keys) {
            const auto mapped = connection_streams.find(key);
            if (mapped == connection_streams.end()) {
                continue;
            }
            std::erase(conn.pending_subscriptions, mapped->second.stream);
            unmap_stream(mapped);
            forget(key);
            if (!has_handle(key)) {
                listeners.erase(key);
            }
            rejections[key] = rejection;
        }
        emit({WebsocketEventType::Error, name + " failed: " + payload, 0, conn.id});
        unconfirm(keys, rejection);
    }

    /// A response to a SUBSCRIBE / UNSUBSCRIBE. A rejected SUBSCRIBE drops its streams.
    void on_response(detail::Connection& conn, const json::object& response) {
        const auto* id = response.if_contains("id");
        const auto pending = requests.find(&conn);
        if (id == nullptr || id->is_null() || pending == requests.end()) {
            return;
        }
        const auto text = json::serialize(*id);
        const auto it = pending->second.lower_bound(text);
        if (it == pending->second.end() || it->first != text) {
            return;
        }
        const auto request = std::move(it->second);
        pending->second.erase(it);
        settle(conn, request);
        const auto error = error_of(response);
        if (!error) {
            if (request.method == "SUBSCRIBE") {
                std::vector<std::string> keys;
                for (const auto& s : request.streams) {
                    if (const auto* key = route(conn, s)) {
                        keys.push_back(*key);
                    }
                }
                confirm(keys);
            }
            return;
        }
        std::vector<std::string> dropped;
        std::string names;
        for (const auto& s : request.streams) {
            names += (names.empty() ? "" : ", ") + s;
            if (request.method != "SUBSCRIBE") {
                continue;
            }
            for (const auto& key : {stream_key(s, conn.url_path), s}) {
                const auto mapped = connection_streams.find(key);
                if (mapped == connection_streams.end() || mapped->second.connection != &conn) {
                    continue;
                }
                std::erase(conn.pending_subscriptions, s);
                unmap_stream(mapped);
                forget(key);
                if (!has_handle(key)) {
                    listeners.erase(key);
                }
                dropped.push_back(key);
            }
        }
        Logger::warn("WebsocketStreams: " + request.method + " rejected on connection " + conn.id +
                     ": " + *error);
        Logger::debug("WebsocketStreams: " + request.method + " rejected for " + names);
        emit({WebsocketEventType::Error, request.method + " failed for " + names + ": " + *error, 0,
              conn.id});
        if (!dropped.empty()) {
            const auto rejection =
                std::make_exception_ptr(WebsocketResponseError(error_code(response), *error));
            for (const auto& key : dropped) {
                rejections[key] = rejection;
            }
            unconfirm(dropped, rejection);
        }
    }

    bool on_message(detail::Connection& conn, const detail::Socket& socket, std::string_view text,
                    bool retired) override {
        json::value msg;
        try {
            msg = parse_json(text);
        } catch (const std::exception& e) {
            Logger::error("WebsocketStreams: failed to parse a message: " + std::string(e.what()));
            return !retired;
        }
        const auto* obj = msg.if_object();
        if (obj == nullptr) {
            return !retired;
        }
        const auto* data = obj->if_contains("data");
        json::value parsed;
        const json::value* stream = nullptr;
        if (signed_streams) {
            const auto* type = obj->if_contains("type");
            if (type != nullptr && type->is_string() && type->get_string() == "COMMAND") {
                on_command(conn, socket, *obj, retired);
                return !retired;
            }
            stream = obj->if_contains("topic");
            if (data != nullptr && data->is_string()) {
                // The payload is JSON text; anything else is delivered as it is.
                try {
                    parsed = parse_json(data->get_string());
                    data = &parsed;
                } catch (const std::exception&) { // NOLINT(bugprone-empty-catch): not JSON, as is
                }
            }
        } else {
            stream = obj->if_contains("stream");
        }
        if (stream == nullptr || !stream->is_string() || data == nullptr) {
            if (!signed_streams) {
                on_response(conn, *obj);
            }
            return !retired;
        }
        const std::string name(stream->get_string());
        const auto* key = route(conn, name);
        if (retired) {
            // The new socket carries the same streams: the previous one only fills the gap
            // until it delivers them.
            if (key == nullptr || !hands_over(conn, name)) {
                return false;
            }
        } else if (const auto h = handovers.find(&conn); h != handovers.end()) {
            if (Clock::now() >= h->second.until) {
                handovers.erase(h);
            } else {
                h->second.started.insert(name);
            }
        }
        if (key != nullptr) {
            // Callbacks may change the subscriptions: `key` is not used past this point.
            if (const auto it = listeners.find(*key); it != listeners.end()) {
                it->second.deliver(*data, gate());
            }
        }
        return true;
    }
};

namespace detail {

void set_signed_ping_interval_for_testing(std::chrono::milliseconds interval) noexcept {
    signed_ping_interval_override = interval.count();
}

} // namespace detail

WebsocketStreams::WebsocketStreams(WebsocketStreamsConfig configuration,
                                   std::vector<std::string> url_paths,
                                   detail::ClientOptions options)
    : impl_(std::make_shared<Impl>(std::move(configuration), std::move(url_paths), options)) {
    impl_->start();
}

WebsocketStreams::~WebsocketStreams() {
    impl_->stop();
}

const WebsocketStreamsConfig& WebsocketStreams::configuration() const noexcept {
    return impl_->cfg;
}

asio::any_io_executor WebsocketStreams::get_executor() const noexcept {
    return impl_->executor();
}

namespace {

/// Runs `start(complete)` on the strand and completes `handler` on its associated executor.
/// `slot`, when connected, is the handler's cancellation slot: it is cleared before the handler
/// runs.
template <class Start>
void initiate(detail::WebsocketCommon& impl,
              asio::any_completion_handler<void(std::exception_ptr)> handler, Start start,
              asio::cancellation_slot slot = {}) {
    auto handler_ex = asio::prefer(asio::get_associated_executor(handler, impl.executor()),
                                   asio::execution::outstanding_work.tracked);
    asio::dispatch(impl.executor(), [keep = impl.shared_from_this(), handler = std::move(handler),
                                     handler_ex, start = std::move(start), slot]() mutable {
        auto shared = std::make_shared<asio::any_completion_handler<void(std::exception_ptr)>>(
            std::move(handler));
        start([shared, handler_ex, slot](std::exception_ptr ep) mutable {
            asio::dispatch(handler_ex, [shared, ep, slot]() mutable {
                if (slot.is_connected()) {
                    slot.clear();
                }
                if (*shared) {
                    detail::run_handler([&] { std::move (*shared)(ep); });
                }
            });
        });
    });
}

} // namespace

void WebsocketStreams::start_connect(std::vector<std::string> streams,
                                     asio::any_completion_handler<ConnectSignature> handler) {
    Impl* impl = impl_.get();
    std::exception_ptr invalid;
    try {
        Impl::check_streams(streams);
        impl->mark_connect_streams(streams);
    } catch (...) {
        invalid = std::current_exception();
    }
    initiate(*impl, std::move(handler),
             [impl, invalid, streams = std::move(streams)](auto complete) mutable {
                 if (invalid) {
                     complete(invalid);
                     return;
                 }
                 try {
                     impl->connect(streams, complete);
                 } catch (...) {
                     complete(std::current_exception());
                 }
             });
}

void WebsocketStreams::connect(std::vector<std::string> streams) {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("connect", "async_connect");
    }
    async_connect(std::move(streams), asio::use_future).get();
}

void WebsocketStreams::start_disconnect(asio::any_completion_handler<ConnectSignature> handler) {
    Impl* impl = impl_.get();
    impl->reset_state();
    initiate(*impl, std::move(handler), [impl](auto complete) {
        impl->clear();
        impl->disconnect_all(complete);
    });
}

void WebsocketStreams::disconnect() {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("disconnect", "async_disconnect");
    }
    async_disconnect(asio::use_future).get();
}

void WebsocketStreams::start_wait_subscribed(
    std::string stream, std::optional<std::string> url_path,
    asio::any_completion_handler<ConnectSignature> handler) {
    start_wait(impl_, stream_key(stream, non_empty(url_path)), std::move(handler));
}

void WebsocketStreams::start_wait(const std::shared_ptr<Impl>& owner, std::string key,
                                  asio::any_completion_handler<ConnectSignature> handler) {
    Impl* impl = owner.get();
    auto ticket = std::make_shared<Impl::WaitTicket>();
    auto slot = asio::get_associated_cancellation_slot(handler);
    if (slot.is_connected()) {
        // Any cancellation type ends the wait: it has no side effect to undo.
        slot.assign([weak = std::weak_ptr<Impl>(owner), key, ticket](asio::cancellation_type type) {
            if (type == asio::cancellation_type::none) {
                return;
            }
            ticket->cancelled = true;
            if (const auto self = weak.lock()) {
                self->post([self = self.get(), key, ticket] { self->cancel_waiter(key, *ticket); });
            }
        });
    }
    initiate(
        *impl, std::move(handler),
        [impl, key = std::move(key), ticket](auto complete) {
            impl->wait_subscribed(key, complete, *ticket);
        },
        slot);
}

void WebsocketStreams::wait_subscribed(std::string stream, std::optional<std::string> url_path,
                                       std::optional<std::chrono::milliseconds> timeout) {
    if (!impl_->may_block()) {
        throw detail::blocking_call_error("wait_subscribed", "async_wait_subscribed");
    }
    if (!timeout) {
        async_wait_subscribed(std::move(stream), std::move(url_path), asio::use_future).get();
        return;
    }
    asio::cancellation_signal signal;
    auto done =
        async_wait_subscribed(std::move(stream), std::move(url_path),
                              asio::bind_cancellation_slot(signal.slot(), asio::use_future));
    if (done.wait_for(*timeout) == std::future_status::timeout) {
        signal.emit(asio::cancellation_type::terminal);
        try {
            done.get();
        } catch (const WebsocketCancelledError&) {
            throw WebsocketTimeoutError();
        }
        return; // acknowledged just before the cancellation took effect
    }
    done.get();
}

bool WebsocketStreams::is_connected() const {
    return impl_->connected();
}

void WebsocketStreams::ping_server() {
    impl_->post([impl = impl_.get()] { impl->ping_server(); });
}

Subscription WebsocketStreams::add_event_callback(detail::Callback<WebsocketEvent> callback,
                                                  bool with_messages) {
    return impl_->add_event_callback(std::move(callback), with_messages);
}

void WebsocketStreams::subscribe(const std::vector<std::string>& streams,
                                 std::optional<StreamId> id,
                                 const std::optional<std::string>& url_path) {
    auto path = non_empty(url_path);
    Impl::check_streams(streams);
    impl_->check_url_path(path);
    impl_->mark_subscribed(streams, path);
    impl_->execute_or_post([impl = impl_.get(), streams, id = impl_->request_id(id), path] {
        impl->subscribe(streams, id, path, false);
    });
}

void WebsocketStreams::unsubscribe(const std::vector<std::string>& streams,
                                   std::optional<StreamId> id,
                                   const std::optional<std::string>& url_path) {
    auto path = non_empty(url_path);
    impl_->mark_unsubscribed(streams, path);
    impl_->execute_or_post([impl = impl_.get(), streams, id = impl_->request_id(id), path] {
        impl->unsubscribe(streams, id, path);
    });
}

bool WebsocketStreams::is_subscribed(const std::string& stream) const {
    return impl_->is_subscribed(stream);
}

WebsocketStreamHandle WebsocketStreams::create_stream(std::string stream,
                                                      std::optional<StreamId> id,
                                                      std::optional<std::string> url_path) {
    url_path = non_empty(url_path);
    Impl::check_streams({stream});
    impl_->check_url_path(url_path);
    const auto key = stream_key(stream, url_path);
    // UNSUBSCRIBE reuses the handle's id.
    auto request_id = impl_->request_id(id);
    const auto epoch = impl_->add_handle(key);
    impl_->execute_or_post([impl = impl_.get(), stream, request_id, url_path, epoch] {
        if (impl->is_current(epoch)) {
            impl->subscribe({stream}, request_id, url_path, true);
        }
    });
    const std::weak_ptr<Impl> weak = impl_;
    auto add = [weak, key, epoch](std::shared_ptr<detail::StreamSlot> slot) {
        if (const auto impl = weak.lock()) {
            impl->execute_or_post(
                [impl = impl.get(), key, epoch, slot = std::move(slot)]() mutable {
                    // Unsubscribed while this was queued (adding it would keep the stream alive),
                    // or the handle predates a disconnect().
                    if (!slot->active || !impl->is_current(epoch)) {
                        return;
                    }
                    impl->listeners[key].add(std::move(slot), impl->gate());
                });
        }
    };
    auto remove = [weak, key, stream, request_id, url_path,
                   epoch](std::vector<std::shared_ptr<detail::StreamSlot>> slots, bool /*wait*/) {
        const auto impl = weak.lock();
        // A handle that predates a disconnect() has nothing left to remove.
        if (!impl || !impl->remove_handle(key, epoch)) {
            return;
        }
        impl->execute_or_post(
            [impl = impl.get(), key, stream, request_id, url_path, slots = std::move(slots)] {
                if (const auto it = impl->listeners.find(key); it != impl->listeners.end()) {
                    it->second.remove(slots);
                }
                impl->unsubscribe({stream}, request_id, url_path);
            });
    };
    auto wait = [weak, key](asio::any_completion_handler<ConnectSignature> handler) {
        if (const auto impl = weak.lock()) {
            start_wait(impl, key, std::move(handler));
            return;
        }
        detail::complete_later(std::move(handler),
                               std::make_exception_ptr(WebsocketCancelledError()));
    };
    auto may_block = [weak] {
        const auto impl = weak.lock();
        return !impl || impl->may_block();
    };
    return {std::move(stream),
            std::make_shared<detail::FunctionStreamBinding>(std::move(add), std::move(remove),
                                                            std::move(wait), std::move(may_block))};
}

std::string WebsocketStreams::stream_key(const std::string& stream,
                                         const std::optional<std::string>& url_path) {
    return url_path && !url_path->empty() ? *url_path + "::" + stream : stream;
}

} // namespace binance::common
