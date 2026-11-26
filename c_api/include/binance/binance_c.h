/*
 * Binance C++ Connector
 * https://github.com/binance/binance-connector-cpp
 *
 * Distributed under the MIT License. See the LICENCE file.
 * Documentation: https://binance.github.io/binance-connector-cpp/
 */

/* C interface to binance::common, for language bindings.
 *
 * - Configuration and requests are JSON strings; the library signs, encodes and sends them.
 * - Calls never throw. Failures are reported as a `bnc_error`.
 * - Callbacks run on a library thread. They must return quickly and must not call
 *   `bnc_*_free` for the object they belong to. Pointers they receive are valid only during
 *   the call.
 * - One process-wide I/O thread pool serves every client (`bnc_set_thread_count`).
 * - A client can be freed while its operations are pending: they complete with
 *   `BNC_ERROR_CANCELLED`, possibly after `bnc_*_free` returns. `user_data` must outlive them.
 * - Callbacks must not throw or unwind into the library. The library carries its own C++ runtime,
 *   so a C++ exception from a caller's callback cannot be caught there, and a managed exception
 *   escaping a reverse P/Invoke ends the process.
 * - Enums are 32-bit. The struct layouts are fixed (the library asserts them at compile time):
 *   `bnc_error` is 600 bytes on every platform; `bnc_rest_response` and `bnc_client_options`
 *   follow the pointer size (P): every member P-aligned, 5P and 3P bytes.
 */
#ifndef BINANCE_C_H
#define BINANCE_C_H

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32)
#if defined(BINANCE_C_BUILDING)
#define BNC_API __declspec(dllexport)
#else
#define BNC_API __declspec(dllimport)
#endif
#else
#define BNC_API __attribute__((visibility("default")))
#endif

/* Every function and callback uses the C calling convention. It is spelled out because 32-bit
 * Windows has others (a binding must declare cdecl too: .NET defaults to stdcall there). */
#if defined(_WIN32)
#define BNC_CALL __cdecl
#else
#define BNC_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Incremented on every incompatible change to this header. Bindings must compare it at load. */
#define BNC_ABI_VERSION 5

BNC_API uint32_t BNC_CALL bnc_abi_version(void);
/* The binance-connector-cpp version, e.g. "1.0.0". */
BNC_API const char* BNC_CALL bnc_version(void);

/* Threads of the shared I/O pool. Takes effect only before the first client is created.
 * Default: 2. */
BNC_API void BNC_CALL bnc_set_thread_count(uint32_t threads);

typedef enum bnc_log_level {
    BNC_LOG_DEBUG = 0,
    BNC_LOG_INFO = 1,
    BNC_LOG_WARN = 2,
    BNC_LOG_ERROR = 3,
    BNC_LOG_NONE = 4
} bnc_log_level;

/* Called from any thread with the message of a library log line. */
typedef void(BNC_CALL* bnc_log_callback)(void* user_data, bnc_log_level level, const char* message,
                                         size_t message_len);

/* Process-wide. The default level is info, or the one named by the LOG_LEVEL environment
 * variable. */
BNC_API void BNC_CALL bnc_set_log_level(bnc_log_level level);
/* Replaces the output (stderr by default); NULL restores it. A call already running may finish
 * after this returns. */
BNC_API void BNC_CALL bnc_set_log_callback(bnc_log_callback callback, void* user_data);

typedef enum bnc_error_kind {
    BNC_OK = 0,
    BNC_ERROR_CONFIG = 1,      /* invalid configuration or request JSON, or an unusable key */
    BNC_ERROR_BAD_REQUEST = 2, /* 400 */
    BNC_ERROR_UNAUTHORIZED = 3,
    BNC_ERROR_FORBIDDEN = 4,
    BNC_ERROR_NOT_FOUND = 5,
    BNC_ERROR_RATE_LIMIT_BAN = 6, /* 418 */
    BNC_ERROR_TOO_MANY_REQUESTS = 7,
    BNC_ERROR_SERVER = 8,
    BNC_ERROR_NETWORK = 9,
    BNC_ERROR_TIMEOUT = 10,
    BNC_ERROR_CANCELLED = 11,
    BNC_ERROR_CLIENT = 12,    /* unexpected status, malformed response, ... */
    BNC_ERROR_WEBSOCKET = 13, /* any other WebSocket failure */
    BNC_ERROR_INTERNAL = 14,
    BNC_ERROR_CONFLICT = 15 /* 409 */
} bnc_error_kind;

/* The kind of a WebSocket failure, in `bnc_error.ws_kind`. */
typedef enum bnc_ws_error_kind {
    BNC_WS_NONE = 0, /* not a WebSocket failure */
    BNC_WS_TIMEOUT = 1,
    BNC_WS_NOT_CONNECTED = 2,
    BNC_WS_NO_RESPONSE = 3,    /* the connection closed before the response arrived */
    BNC_WS_RESPONSE_ERROR = 4, /* the server answered with an error status */
    BNC_WS_HANDSHAKE = 5,      /* the upgrade was rejected or failed */
    BNC_WS_PROTOCOL = 6,
    BNC_WS_SERVER = 7,
    BNC_WS_NETWORK = 8,
    BNC_WS_CANCELLED = 9,
    BNC_WS_OTHER = 10
} bnc_ws_error_kind;

typedef struct bnc_error {
    bnc_error_kind kind;
    /* HTTP status of the failing response, or 0. */
    int32_t http_status;
    /* Binance error code from the response body, valid if `has_code`. */
    int32_t has_code;
    /* Padding made explicit, so the layout is the same on every platform. Always 0. */
    int32_t reserved0;
    int64_t code;
    /* `Retry-After` in seconds (REST), or -1. */
    int64_t retry_after_seconds;
    /* Epoch milliseconds from `error.data.retryAfter` (WebSocket API), or -1. */
    int64_t retry_at_ms;
    /* The underlying system error, if any: its value and category name ("system", ...).
     * 0 / "" otherwise. */
    int32_t transport_code;
    char transport_category[32];
    /* Whether the request may have reached the server. Always 1 if `http_status` is not 0. */
    int32_t request_sent;
    char message[512];
    /* The WebSocket failure behind `kind`, or BNC_WS_NONE for other failures. */
    bnc_ws_error_kind ws_kind;
    int32_t reserved1; /* always 0 */
} bnc_error;

/* A pending request, for cancelling it. Optional: functions that start a request accept NULL
 * for it. */
typedef struct bnc_request bnc_request;

/* Cancels the request: its callback is called with BNC_ERROR_CANCELLED, unless it has already
 * completed or its response has arrived. Whether the server received the request is
 * `request_sent` in the error. Safe from any thread and after completion.
 *
 * REST requests and `bnc_wsapi_send` are aborted when cancelled. The other
 * operations that return a handle (`bnc_streams_connect`, `bnc_streams_disconnect`,
 * `bnc_wsapi_connect`, `bnc_wsapi_disconnect`, `bnc_wsapi_subscribe`) cannot be aborted: cancelling
 * one abandons the wait. Its callback is called at once with BNC_ERROR_CANCELLED, and the
 * operation goes on; its real completion is dropped. A connect may still open the connections, a
 * disconnect may still close them (and end the streams), and a subscribe may still open the
 * subscription on the server (the library then ends it, as `bnc_stream_free` would). */
BNC_API void BNC_CALL bnc_request_cancel(bnc_request* request);
/* Releases the handle (it does not cancel). Safe after completion. */
BNC_API void BNC_CALL bnc_request_release(bnc_request* request);

/* ---- REST ------------------------------------------------------------------------------- */

typedef struct bnc_rest_client bnc_rest_client;

typedef struct bnc_rest_response {
    int32_t status;
    const char* body;
    size_t body_len;
    /* JSON object of the response headers (lower-case names), and the parsed rate limits as a
     * JSON array ("[]" if none). */
    const char* headers_json;
    const char* rate_limits_json;
} bnc_rest_response;

/* Completion of a request: `response` alone on success; `error` on failure, with `response` the
 * HTTP response that caused it (status, body, headers, rate limits) when the server answered, else
 * NULL. Both are valid only during the call. */
typedef void(BNC_CALL* bnc_rest_callback)(void* user_data, const bnc_error* error,
                                          const bnc_rest_response* response);

/* Called while a TLS handshake verifies the server's certificate chain (and the certificate of an
 * https proxy), once per certificate: `depth` 0 is the server certificate, higher depths its
 * issuers. `cert_der` is the certificate in DER form, valid only during the call. `preverified` is
 * 1 if the library's own checks (trusted chain, validity, host name) found no problem with this
 * certificate so far, else 0. Return 1 to accept the certificate and 0 to reject it, which fails
 * the handshake with a TLS error. Pinning: reject the certificate at the depth that carries the pin
 * (and return `preverified` for the others). Returning 1 for a certificate with `preverified` 0
 * accepts it anyway, which disables the verification for the connection.
 *
 * It runs on library threads, possibly several at a time, and must return quickly. */
typedef int32_t(BNC_CALL* bnc_tls_verify_callback)(void* user_data, const uint8_t* cert_der,
                                                   size_t cert_der_len, int32_t depth,
                                                   int32_t preverified);

/* Returns the `timestamp` (epoch milliseconds) for a signed request, signed WebSocket API request
 * or signed stream URL, including retries, re-logons, reconnects and renewals. It runs on library
 * threads, possibly several at a time, must return quickly and must not call back into the library.
 */
typedef int64_t(BNC_CALL* bnc_timestamp_callback)(void* user_data);

/* Options of `bnc_rest_new_ex`, `bnc_wsapi_new_ex` and `bnc_streams_new_ex`. Set `struct_size` to
 * `sizeof(bnc_client_options)`; fields added later are read only if `struct_size` covers them, so
 * a binding built against an older header keeps working. Zero the other fields you do not use. */
typedef struct bnc_client_options {
    uint32_t struct_size;
    /* Called for every certificate chain the client verifies; NULL: only the built-in checks. */
    bnc_tls_verify_callback tls_verify;
    /* `tls_verify` receives it. It must outlive the client. */
    void* tls_verify_data;
    /* Source of the `timestamp` of signed requests; NULL: the host clock (plus `time_offset_ms`).
     * Setting both it and `time_offset_ms` is a BNC_ERROR_CONFIG. */
    bnc_timestamp_callback timestamp;
    /* `timestamp` receives it. It must outlive the client. */
    void* timestamp_data;
} bnc_client_options;

/* `config_json` keys (all optional unless noted):
 *   base_path (required), api_key, api_secret, private_key_pem, private_key_file,
 *   private_key_passphrase, timeout_ms, retries, backoff_ms, keep_alive, compression,
 *   max_response_size, time_unit ("MILLISECOND" | "MICROSECOND"), time_offset_ms (integer,
 *   added to the host clock for the `timestamp` of signed requests; may be negative; also a key
 *   of the WebSocket API and streams configs), user_agent, proxy_from_env,
 *   custom_headers {name: value}, proxy {host, port, protocol "http"|"https"|"socks5"|"socks5h",
 *   username, password}, ca_file, ca_pem, ca_only, client_cert_pem, client_cert_file,
 * client_key_pem, client_key_file, client_key_passphrase.
 *
 * `proxy`: "http" and "https" (TLS to the proxy itself) use Basic credentials. "socks5" and
 * "socks5h" are SOCKS5 over plain TCP, with username / password (at most 255 bytes each) if given;
 * "socks5" resolves the target's host name in the client, "socks5h" has the proxy resolve it. TLS
 * to the target runs end to end through the tunnel. Without `proxy`, `proxy_from_env` reads the
 * environment (https_proxy, http_proxy, all_proxy, no_proxy), where all_proxy and the others may
 * hold socks5:// and socks5h:// URLs.
 *
 * TLS: the system trust store is always loaded first. `ca_file` (path to a PEM bundle) and `ca_pem`
 * (PEM text) add the CAs they hold to it, e.g. a private CA; with both, both are added. With
 * `ca_only` true, the system store is dropped and only those CAs are trusted (it needs `ca_file` or
 * `ca_pem`). They apply to the target and to an https proxy. An unreadable file or invalid PEM is a
 * BNC_ERROR_CONFIG. Verification cannot be switched off by a key; use `tls_verify` in
 * `bnc_client_options` for pinning or to take over the decision.
 *
 * Client certificates (mutual TLS): `client_cert_pem` or `client_cert_file` (the certificate, then
 * its chain, in PEM) with `client_key_pem` or `client_key_file` (its PEM private key) and, for an
 * encrypted key, `client_key_passphrase`. They are keys of the three configs; the certificate and
 * the key go together, and a key that does not match the certificate is a BNC_ERROR_CONFIG.
 *
 * Integers must be in range, or the configuration is a BNC_ERROR_CONFIG: `retries` and `pool_size`
 * are not negative, `max_response_size` and `max_message_size` are at least 1, a proxy `port` is
 * 1-65535.
 *
 * Returns NULL and fills `error` on failure. An unusable private key (invalid PEM, unreadable
 * file, wrong passphrase) is a BNC_ERROR_CONFIG. */
BNC_API bnc_rest_client* BNC_CALL bnc_rest_new(const char* config_json, bnc_error* error);
/* As `bnc_rest_new`, with options (NULL for none). */
BNC_API bnc_rest_client* BNC_CALL bnc_rest_new_ex(const char* config_json,
                                                  const bnc_client_options* options,
                                                  bnc_error* error);
BNC_API void BNC_CALL bnc_rest_free(bnc_rest_client* client);

/* `request_json`: {"method": "GET"|"POST"|"PUT"|"DELETE"|"PATCH", "endpoint": "/api/v3/time",
 * "query": {...}, "body": {...}, "signed": false, "time_unit": "MILLISECOND",
 * "headers": {name: value}}. Values are plain JSON; the library encodes them and signs.
 * Numbers: an integer that fits in 64 bits stays a number. Any other number (with a fraction or an
 * exponent, or a larger integer) is taken exactly as written, never through a double, and sent as a
 * plain decimal string: 0.1 → "0.1", 1.5e-7 → "0.00000015". The same holds for `params` of the
 * WebSocket API. Prices and quantities may also be given as strings.
 * Returns 0 if the request was started (and `callback` will be called once), else the error is
 * in `error` and `callback` is not called. */
BNC_API int32_t BNC_CALL bnc_rest_send(bnc_rest_client* client, const char* request_json,
                                       bnc_rest_callback callback, void* user_data,
                                       bnc_request** out_request, bnc_error* error);

/* ---- WebSocket Streams ------------------------------------------------------------------ */

typedef struct bnc_streams bnc_streams;
typedef struct bnc_stream bnc_stream;

/* Completion of connect / disconnect: `error` is NULL on success. */
typedef void(BNC_CALL* bnc_status_callback)(void* user_data, const bnc_error* error);
/* A stream payload (the event JSON). */
typedef void(BNC_CALL* bnc_message_callback)(void* user_data, const char* data, size_t data_len);

typedef enum bnc_event_type {
    BNC_EVENT_OPEN = 0,
    BNC_EVENT_MESSAGE = 1,
    BNC_EVENT_ERROR = 2,
    BNC_EVENT_CLOSE = 3,
    BNC_EVENT_PING = 4,
    BNC_EVENT_PONG = 5
} bnc_event_type;

typedef void(BNC_CALL* bnc_event_callback)(void* user_data, bnc_event_type type, const char* data,
                                           size_t data_len, uint16_t close_code,
                                           const char* connection_id);

/* `config_json` keys: url (required), reconnect_delay_ms, connect_timeout_ms, pool_size
 * (0 = single connection), compression, max_message_size, time_unit, user_agent,
 * proxy_from_env, proxy {...}, ca_file, ca_pem, ca_only, client_cert_* / client_key_* (proxy and
 * TLS keys as for `bnc_rest_new`), stream_id_is_strictly_number (boolean: SUBSCRIBE / UNSUBSCRIBE
 * ids are always numbers; a string id given to `bnc_stream_new` is replaced by a number), and for
 * signed streams: signed_streams, api_key, api_secret, private_key_pem, private_key_file,
 * private_key_passphrase (an unusable key is a BNC_ERROR_CONFIG). `url_paths_json`: optional JSON
 * array of URL paths, e.g. ["market","public"]. */
BNC_API bnc_streams* BNC_CALL bnc_streams_new(const char* config_json, const char* url_paths_json,
                                              bnc_error* error);
/* As `bnc_streams_new`, with options (NULL for none). */
BNC_API bnc_streams* BNC_CALL bnc_streams_new_ex(const char* config_json,
                                                 const char* url_paths_json,
                                                 const bnc_client_options* options,
                                                 bnc_error* error);
/* Ends the streams still alive (see `bnc_stream_new`), then closes the client. After
 * it returns no callback starts, except the completions of pending operations, which complete
 * with `BNC_ERROR_CANCELLED` (possibly after it returns). */
BNC_API void BNC_CALL bnc_streams_free(bnc_streams* streams);

/* `streams_json`: optional JSON array of stream names put in the connection URL.
 * `out_request` (optional) receives a handle for `bnc_request_cancel`, which abandons the wait (the
 * connection attempt goes on); release it with `bnc_request_release`. */
BNC_API int32_t BNC_CALL bnc_streams_connect(bnc_streams* streams, const char* streams_json,
                                             bnc_status_callback callback, void* user_data,
                                             bnc_request** out_request, bnc_error* error);
/* Drops every subscription, then closes the connections. The streams that exist when it is called
 * end (`bnc_stream_new`) when it completes, also if the wait was abandoned with
 * `bnc_request_cancel`. `out_request` as for `bnc_streams_connect`. */
BNC_API int32_t BNC_CALL bnc_streams_disconnect(bnc_streams* streams, bnc_status_callback callback,
                                                void* user_data, bnc_request** out_request,
                                                bnc_error* error);
BNC_API int32_t BNC_CALL bnc_streams_is_connected(const bnc_streams* streams);
/* 1 if `stream` is subscribed (or queued until its connection opens), on any URL path: through
 * `bnc_stream_new` or `bnc_streams_connect`, until it is unsubscribed (`bnc_stream_free` of its
 * last handle), rejected by the server or dropped by `bnc_streams_disconnect`. 0 if it is not, and
 * -1 if `streams` or `stream` is NULL or the check failed. */
BNC_API int32_t BNC_CALL bnc_streams_is_subscribed(const bnc_streams* streams, const char* stream);
/* Sends a WebSocket ping frame on every open connection. */
BNC_API int32_t BNC_CALL bnc_streams_ping(bnc_streams* streams, bnc_error* error);

/* Events (open, message, close, error, ping, ...) of every connection. NULL removes it. After
 * this returns the previous callback is not started again (a call already running on another
 * thread finishes first; one made from a library callback is not waited for). The new callback
 * takes over from the previous one between two events: none is lost or delivered to both, except
 * when this is called from a library callback. */
BNC_API void BNC_CALL bnc_streams_set_event_callback(bnc_streams* streams,
                                                     bnc_event_callback callback, void* user_data);
/* As `bnc_streams_set_event_callback`, but without BNC_EVENT_MESSAGE: messages are not even built
 * unless some other callback wants them. Replaces either kind of callback. */
BNC_API void BNC_CALL bnc_streams_set_lifecycle_callback(bnc_streams* streams,
                                                         bnc_event_callback callback,
                                                         void* user_data);

/* Calls `callback` once the server has acknowledged the subscription of `stream` (as given to
 * `bnc_stream_new`, with the same `url_path`): at once if it already has; it waits while the
 * client connects or reconnects. `error` is NULL on success; the server's rejection of the
 * SUBSCRIBE (BNC_ERROR_WEBSOCKET, BNC_WS_RESPONSE_ERROR); or BNC_ERROR_CANCELLED if the stream is
 * not subscribed, or stops being before (`bnc_stream_free`, `bnc_streams_disconnect`,
 * `bnc_streams_free`). `out_request` as for `bnc_streams_connect`: cancelling abandons the wait. */
BNC_API int32_t BNC_CALL bnc_streams_wait_subscribed(bnc_streams* streams, const char* stream,
                                                     const char* url_path,
                                                     bnc_status_callback callback, void* user_data,
                                                     bnc_request** out_request, bnc_error* error);

/* Subscribes to the stream names of `streams_json` (a JSON array) without a handle: their messages
 * reach the event callback (`bnc_streams_set_event_callback`) and the handles of the same streams.
 * Queued until a connection opens; kept across reconnects. `url_path` and `id_json` as for
 * `bnc_stream_new`. `bnc_streams_unsubscribe` sends UNSUBSCRIBE for them, whatever subscribed them
 * (the handles of those streams then receive nothing more). Return 0, or -1 and fill `error`. */
BNC_API int32_t BNC_CALL bnc_streams_subscribe(bnc_streams* streams, const char* streams_json,
                                               const char* url_path, const char* id_json,
                                               bnc_error* error);
BNC_API int32_t BNC_CALL bnc_streams_unsubscribe(bnc_streams* streams, const char* streams_json,
                                                 const char* url_path, const char* id_json,
                                                 bnc_error* error);

/* Subscribes to `stream` (queued until a connection opens). `url_path` may be NULL. `id_json` is
 * the SUBSCRIBE request id, a JSON number or string, or NULL for a generated one.
 *
 * `on_terminated` (optional) is called at most once, when the client will deliver no more messages
 * for the stream:
 *   - the server rejected its SUBSCRIBE: `error` is a BNC_ERROR_WEBSOCKET describing it;
 *   - `bnc_streams_disconnect` completed, or `bnc_streams_free` was called: `error` is NULL.
 * It is not called when a connection is lost and the library reconnects, nor after
 * `bnc_stream_free` returned. It runs on a library thread; it may call `bnc_stream_free` for its
 * own stream.
 * Returns NULL and fills `error` on failure. */
BNC_API bnc_stream* BNC_CALL bnc_stream_new(bnc_streams* streams, const char* stream,
                                            const char* url_path, const char* id_json,
                                            bnc_message_callback callback, void* user_data,
                                            bnc_status_callback on_terminated,
                                            void* terminated_data, bnc_error* error);
/* 1 while the stream is subscribed (or queued), 0 once `on_terminated` applies to it. Always 1
 * for a stream from `bnc_wsapi_subscribe`. */
BNC_API int32_t BNC_CALL bnc_stream_is_active(const bnc_stream* stream);
/* Unsubscribes (when no other handle uses the stream) and frees the handle. After it returns,
 * neither `callback` nor `on_terminated` is started again (one already running finishes first). */
BNC_API void BNC_CALL bnc_stream_free(bnc_stream* stream);

/* ---- WebSocket API ---------------------------------------------------------------------- */

typedef struct bnc_wsapi bnc_wsapi;

/* Completion of a request: `error` is NULL on success. `responses_json` is a JSON array with one
 * element per answering connection (one, except for session.logon / session.logout):
 * [{"result": ..., "rateLimits": [...]}]. On an error answered by the server
 * (BNC_WS_RESPONSE_ERROR) it is {"rateLimits": [...], "data": ...}: the rate limits of that answer,
 * and its `error.data` as Binance sent it (only when it has one); else NULL.
 */
typedef void(BNC_CALL* bnc_wsapi_callback)(void* user_data, const bnc_error* error,
                                           const char* responses_json, size_t responses_len);

/* Completion of a subscription: `error` is NULL on success, and then `stream` is owned by the
 * callee, to be released with `bnc_stream_free`. `response_json` is {"result": ..., "rateLimits":
 * [...]}; on an error answered by the server, {"rateLimits": [...], "data": ...} as for
 * `bnc_wsapi_callback`.
 * Events reach the message callback given to `bnc_wsapi_subscribe`. */
typedef void(BNC_CALL* bnc_wsapi_subscribe_callback)(void* user_data, const bnc_error* error,
                                                     const char* response_json, size_t response_len,
                                                     bnc_stream* stream);

/* `config_json` keys: url (required), api_key, api_secret, private_key_pem, private_key_file,
 * private_key_passphrase, timeout_ms, reconnect_delay_ms, connect_timeout_ms, pool_size
 * (0 = single connection), compression, max_message_size, time_unit, auto_session_relogon,
 * user_agent, proxy_from_env, proxy {...}, ca_file, ca_pem, ca_only, client_cert_* / client_key_*
 * (proxy and TLS keys as for `bnc_rest_new`). An unusable private key is a BNC_ERROR_CONFIG. */
BNC_API bnc_wsapi* BNC_CALL bnc_wsapi_new(const char* config_json, bnc_error* error);
/* As `bnc_wsapi_new`, with options (NULL for none). */
BNC_API bnc_wsapi* BNC_CALL bnc_wsapi_new_ex(const char* config_json,
                                             const bnc_client_options* options, bnc_error* error);
/* Closes the connections at once and fails pending requests with BNC_ERROR_CANCELLED. Call
 * `bnc_wsapi_disconnect` first for a graceful close. After it returns no callback starts, except
 * those completions (possibly after it returns). */
BNC_API void BNC_CALL bnc_wsapi_free(bnc_wsapi* api);

/* `out_request` (optional) receives a handle for `bnc_request_cancel`, which abandons the wait (the
 * connection attempt goes on); release it with `bnc_request_release`. */
BNC_API int32_t BNC_CALL bnc_wsapi_connect(bnc_wsapi* api, bnc_status_callback callback,
                                           void* user_data, bnc_request** out_request,
                                           bnc_error* error);
/* `out_request` as for `bnc_wsapi_connect`; cancelling abandons the wait (the disconnect goes on).
 */
BNC_API int32_t BNC_CALL bnc_wsapi_disconnect(bnc_wsapi* api, bnc_status_callback callback,
                                              void* user_data, bnc_request** out_request,
                                              bnc_error* error);
BNC_API int32_t BNC_CALL bnc_wsapi_is_connected(const bnc_wsapi* api);
/* Sends a WebSocket ping frame on every open connection. */
BNC_API int32_t BNC_CALL bnc_wsapi_ping(bnc_wsapi* api, bnc_error* error);
/* As `bnc_streams_set_event_callback`. */
BNC_API void BNC_CALL bnc_wsapi_set_event_callback(bnc_wsapi* api, bnc_event_callback callback,
                                                   void* user_data);
/* As `bnc_streams_set_lifecycle_callback`. */
BNC_API void BNC_CALL bnc_wsapi_set_lifecycle_callback(bnc_wsapi* api, bnc_event_callback callback,
                                                       void* user_data);

/* `request_json`: {"method": "account.status", "params": {...}, "auth": "none" | "api_key" |
 * "signed" | "session_logon" | "session_logout", "id": "..."}. `auth` defaults to "none". The
 * library adds the id, apiKey, timestamp and signature ("session_logon" is signed).
 * `id` (optional, a string or an integer) is the request id: it is used if it is a string of 32
 * lower-case hexadecimal characters, which is what Binance clients generate; any other value is
 * replaced by a generated id, as is an absent one. An "id" inside `params` is treated the same,
 * and `id` takes precedence. */
BNC_API int32_t BNC_CALL bnc_wsapi_send(bnc_wsapi* api, const char* request_json,
                                        bnc_wsapi_callback callback, void* user_data,
                                        bnc_request** out_request, bnc_error* error);

/* Sends a request that opens a user-data subscription (e.g. userDataStream.subscribe). The
 * library repeats it after every reconnect and renewal, on the connection that made it.
 * `bnc_stream_free` of the delivered stream ends the subscription on the server
 * (userDataStream.unsubscribe with its current subscriptionId, on that connection).
 * `message_callback` receives each event. `request_json` as for `bnc_wsapi_send`. `out_request`
 * (optional) receives a handle for `bnc_request_cancel`, which abandons the wait: `callback` is
 * called at once with BNC_ERROR_CANCELLED (`request_sent` 1), and no stream is delivered even if
 * the subscription is opened. */
BNC_API int32_t BNC_CALL bnc_wsapi_subscribe(bnc_wsapi* api, const char* request_json,
                                             bnc_wsapi_subscribe_callback callback, void* user_data,
                                             bnc_message_callback message_callback,
                                             void* message_data, bnc_request** out_request,
                                             bnc_error* error);

#ifdef __cplusplus
}
#endif

#endif
