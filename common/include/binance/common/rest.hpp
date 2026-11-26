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
#include <optional>
#include <string>
#include <string_view>
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

namespace binance::common {

enum class HttpMethod { Get, Post, Put, Delete, Patch };

[[nodiscard]] BINANCE_COMMON_EXPORT std::string_view to_string(HttpMethod method) noexcept;

/// One REST call, before signing and serialisation.
struct RestRequest {
    HttpMethod method = HttpMethod::Get;
    /// Path relative to `base_path`, e.g. `/api/v3/order`.
    std::string endpoint;
    Params query;
    /// Sent as an `application/x-www-form-urlencoded` body.
    Params body;
    /// Sent as `X-MBX-TIME-UNIT`. Products that support it pass `RestApiConfig::time_unit`.
    std::optional<TimeUnit> time_unit;
    /// Adds `timestamp` and `signature`.
    bool is_signed = false;
    /// Per-request headers. Applied after `custom_headers`, with the same
    /// validation. They cannot replace the headers the SDK sets.
    std::vector<std::pair<std::string, std::string>> headers;
};

/// The REST transport shared by every product.
///
/// It runs on its own I/O thread, or on `configuration.executor` when set, and keeps a
/// keep-alive connection pool. It handles signing, retries, gzip / deflate decoding, rate-limit
/// headers and error mapping.
///
/// Completion handlers run on the handler's associated executor. Without one, they run on
/// the client's executor (`get_executor()`). Errors are delivered as `std::exception_ptr`, which
/// holds a `ConnectorError` subclass.
///
/// Without `configuration.executor`, the executor from `get_executor()` belongs to the client's
/// own I/O context: neither it nor I/O objects created on it may outlive the client. Destruction
/// waits for the I/O thread, which may be held up by a DNS lookup in progress (`getaddrinfo`
/// cannot be interrupted).
class BINANCE_COMMON_EXPORT RestClient {
public:
    using Signature = void(std::exception_ptr, RawResponse);
    using Handler = boost::asio::any_completion_handler<Signature>;

    /// Throws `ConfigError` if `base_path` or `proxy` is invalid, or `ConnectorClientError` if
    /// the private key cannot be loaded.
    explicit RestClient(RestApiConfig configuration, detail::ClientOptions options = {});
    ~RestClient();
    RestClient(const RestClient&) = delete;
    RestClient& operator=(const RestClient&) = delete;
    RestClient(RestClient&&) = delete;
    RestClient& operator=(RestClient&&) = delete;

    /// The configuration, as given but without `private_key_passphrase` (the key is loaded).
    [[nodiscard]] const RestApiConfig& configuration() const noexcept;
    [[nodiscard]] const SignatureGenerator& signature_generator() const noexcept;
    [[nodiscard]] boost::asio::any_io_executor get_executor() const noexcept;

    /// Asynchronous send. `token` may be a callback `void(std::exception_ptr, RawResponse)`,
    /// `boost::asio::use_future`, `boost::asio::use_awaitable`, …
    ///
    /// Supports per-operation cancellation (`bind_cancellation_slot`, parallel groups, or
    /// `cancel_after(timer, duration, token)` with a timer on the caller's executor): the request
    /// then completes with `RequestCancelledError`, whose `request_sent()` says whether it may have
    /// reached the server. Terminal and partial cancellation are always honoured; total
    /// cancellation only until the request starts to be written, and is ignored after that. A
    /// response that has already arrived is delivered instead. Destroying the client cancels every
    /// in-flight request the same way.
    template <class CompletionToken>
    auto async_send_request(RestRequest request, CompletionToken&& token) {
        return boost::asio::async_initiate<CompletionToken, Signature>(
            [this](auto handler, RestRequest req) {
                start(std::move(req), Handler(std::move(handler)));
            },
            token, std::move(request));
    }

    /// Blocking send. Throws a `ConnectorError` subclass on failure.
    /// Must not be called from the client's executor, nor from a thread running a shared one.
    RawResponse send_request(RestRequest request);

private:
    void start(RestRequest request, Handler handler);

    struct Impl;
    std::shared_ptr<Impl> impl_;
};

/// Blocking typed send, as used by the product clients.
template <class T> RestApiResponse<T> send(RestClient& client, RestRequest request) {
    return RestApiResponse<T>(client.send_request(std::move(request)));
}

/// Asynchronous typed send, completing with `void(std::exception_ptr, RestApiResponse<T>)`.
/// `client` is kept alive until the operation completes.
template <class T, class CompletionToken>
auto async_send(std::shared_ptr<RestClient> client, RestRequest request, CompletionToken&& token) {
    return boost::asio::async_initiate<CompletionToken,
                                       void(std::exception_ptr, RestApiResponse<T>)>(
        [](auto handler, std::shared_ptr<RestClient> c, RestRequest req) {
            auto ex = boost::asio::get_associated_executor(handler, c->get_executor());
            auto slot = boost::asio::get_associated_cancellation_slot(handler);
            auto* raw_client = c.get();
            raw_client->async_send_request(
                std::move(req),
                boost::asio::bind_cancellation_slot(
                    slot, boost::asio::bind_executor(
                              std::move(ex), [h = std::move(handler), c = std::move(c)](
                                                 std::exception_ptr ep, RawResponse raw) mutable {
                                  std::move(h)(ep, RestApiResponse<T>(std::move(raw)));
                              })));
        },
        token, std::move(client), std::move(request));
}

} // namespace binance::common
