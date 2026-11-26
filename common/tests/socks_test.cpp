//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// SOCKS5 proxy tests for the REST client and the WebSocket clients, against a local SOCKS5 server.
#include <memory>
#include <string>
#include <vector>

#include <boost/asio/ssl/context.hpp>
#include <boost/json.hpp>
#include <gtest/gtest.h>

#include <binance/common/errors.hpp>
#include <binance/common/rest.hpp>
#include <binance/common/websocket_api.hpp>
#include <binance/common/websocket_streams.hpp>

#include "support/certs.hpp"
#include "support/env.hpp"
#include "support/mock_server.hpp"
#include "support/mock_socks.hpp"
#include "support/mock_ws_server.hpp"

using namespace binance::common;
using namespace std::chrono_literals;
using binance::test::MockServer;
using binance::test::MockSocks;
using binance::test::MockWsServer;
using binance::test::ScopedEnv;
using binance::test::socks_connect_reply;
using binance::test::socks_credentials;
using binance::test::socks_delay;
using binance::test::socks_method_reply;
using binance::test::TestCertificate;
namespace asio = boost::asio;
namespace json = boost::json;

namespace {

std::uint16_t port_of(const std::string& url) {
    return static_cast<std::uint16_t>(std::stoi(url.substr(url.rfind(':') + 1)));
}

std::string with_localhost(std::string url) {
    url.replace(url.find("127.0.0.1"), 9, "localhost");
    return url;
}

ProxyConfig socks_at(const MockSocks& socks, ProxyProtocol protocol,
                     std::optional<ProxyAuth> auth = std::nullopt) {
    return ProxyConfig{"127.0.0.1", socks.port(), protocol, std::move(auth)};
}

void trust(asio::ssl::context& ctx) {
    TestCertificate::get().trust(ctx);
}

RestApiConfig rest_config(const std::string& url, const ProxyConfig& proxy) {
    RestApiConfig cfg;
    cfg.base_path = url;
    cfg.proxy_from_env = false;
    cfg.retries = 0;
    cfg.proxy = proxy;
    cfg.agent = trust;
    return cfg;
}

RestRequest get(std::string endpoint) {
    return RestRequest{HttpMethod::Get, std::move(endpoint), {}, {}, {}, false, {}};
}

void echo(MockWsServer::Session& s, const std::string& text) {
    const auto req = json::parse(text).as_object();
    s.send(json::serialize(json::object{{"id", req.at("id")},
                                        {"status", 200},
                                        {"result", json::object{{"echo", req.at("method")}}}}));
}

WebsocketApiConfig api_config(const std::string& url, const ProxyConfig& proxy) {
    WebsocketApiConfig cfg;
    cfg.url = url;
    cfg.api_key = "api-key";
    cfg.api_secret = "api-secret";
    cfg.timeout = 2000ms;
    cfg.connect_timeout = 2000ms;
    cfg.proxy_from_env = false;
    cfg.proxy = proxy;
    cfg.agent = trust;
    return cfg;
}

WebsocketStreamsConfig streams_config(const std::string& url, const ProxyConfig& proxy) {
    WebsocketStreamsConfig cfg;
    cfg.url = url;
    cfg.connect_timeout = 2000ms;
    cfg.proxy_from_env = false;
    cfg.proxy = proxy;
    cfg.agent = trust;
    return cfg;
}

MockWsServer::Options tls_options() {
    MockWsServer::Options opts;
    opts.tls = TestCertificate::get().server_context();
    return opts;
}

/// Clears every proxy variable for the test, then sets the given ones.
struct ProxyEnv {
    explicit ProxyEnv(std::initializer_list<std::pair<const char*, const char*>> vars) {
        for (const char* name : {"http_proxy", "HTTP_PROXY", "https_proxy", "HTTPS_PROXY",
                                 "all_proxy", "ALL_PROXY", "no_proxy", "NO_PROXY"}) {
            guards.push_back(std::make_unique<ScopedEnv>(name, std::nullopt));
        }
        for (const auto& [name, value] : vars) {
            guards.push_back(std::make_unique<ScopedEnv>(name, value));
        }
    }
    std::vector<std::unique_ptr<ScopedEnv>> guards;
};

} // namespace

// ==== REST ====

TEST(SocksRest, TunnelsAnHttpTargetInOriginForm) {
    MockServer server(
        [](const auto&) { return binance::test::MockResponse{.body = "{\"via\":1}"}; });
    MockSocks socks;
    RestClient client(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, "{\"via\":1}");
    EXPECT_EQ(client.send_request(get("/api/v3/time")).body, "{\"via\":1}");

    const auto seen = socks.requests();
    ASSERT_EQ(seen.size(), 1U); // one tunnel, kept alive
    EXPECT_EQ(seen[0].methods, (std::vector<std::uint8_t>{0}));
    EXPECT_EQ(seen[0].address_type, 1);
    EXPECT_EQ(seen[0].host, "127.0.0.1");
    EXPECT_EQ(server.requests().at(0).target, "/api/v3/time");
    EXPECT_EQ(server.request_count(), 2U);
}

TEST(SocksRest, Socks5ResolvesTheHostNameItself) {
    MockServer server;
    MockSocks socks;
    RestClient client(
        rest_config(with_localhost(server.url()), socks_at(socks, ProxyProtocol::Socks5)));
    (void)client.send_request(get("/x"));
    const auto seen = socks.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_TRUE(seen[0].address_type == 1 || seen[0].address_type == 4) << seen[0].host;
    EXPECT_NE(seen[0].host, "localhost");
    EXPECT_EQ(server.requests().at(0).header("host").substr(0, 9), "localhost");
}

TEST(SocksRest, Socks5hSendsTheHostName) {
    MockServer server;
    MockSocks socks;
    RestClient client(
        rest_config(with_localhost(server.url()), socks_at(socks, ProxyProtocol::Socks5h)));
    (void)client.send_request(get("/x"));
    const auto seen = socks.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_EQ(seen[0].address_type, 3);
    EXPECT_EQ(seen[0].host, "localhost");
    EXPECT_EQ(seen[0].port, port_of(server.url()));
}

TEST(SocksRest, Socks5hSendsIpLiteralsAsAddresses) {
    MockServer server;
    MockSocks socks;
    RestClient client(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5h)));
    (void)client.send_request(get("/x"));
    EXPECT_EQ(socks.requests().at(0).address_type, 1);
}

TEST(SocksRest, TunnelsATlsTargetEndToEnd) {
    MockServer server(
        [](const auto&) { return binance::test::MockResponse{.body = "{\"tls\":1}"}; },
        TestCertificate::get().server_context());
    MockSocks socks;
    // The certificate is for `localhost`: the TLS name check runs against the target, not the
    // proxy.
    RestClient client(
        rest_config(with_localhost(server.url()), socks_at(socks, ProxyProtocol::Socks5h)));
    EXPECT_EQ(client.send_request(get("/x")).body, "{\"tls\":1}");
    EXPECT_EQ(socks.requests().at(0).host, "localhost");
}

TEST(SocksRest, SendsCredentials) {
    MockServer server;
    MockSocks socks(socks_credentials("user", "pa:ss"));
    RestClient client(rest_config(
        server.url(), socks_at(socks, ProxyProtocol::Socks5, ProxyAuth{"user", "pa:ss"})));
    (void)client.send_request(get("/x"));
    const auto seen = socks.requests().at(0);
    EXPECT_EQ(seen.methods, (std::vector<std::uint8_t>{0, 2}));
    EXPECT_EQ(seen.username, "user");
    EXPECT_EQ(seen.password, "pa:ss");
    EXPECT_FALSE(server.requests().at(0).has_header("proxy-authorization"));
}

TEST(SocksRest, WrongCredentialsAreReported) {
    MockServer server;
    MockSocks socks(socks_credentials("user", "secret"));
    RestClient client(rest_config(
        server.url(), socks_at(socks, ProxyProtocol::Socks5, ProxyAuth{"user", "wrong"})));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("authentication failed"), std::string::npos)
            << e.what();
        EXPECT_EQ(e.transport_error(), boost::asio::error::access_denied);
        EXPECT_FALSE(e.request_sent());
    }
    EXPECT_EQ(server.request_count(), 0U);
}

TEST(SocksRest, MissingCredentialsAreReported) {
    MockServer server;
    MockSocks socks(socks_credentials("user", "secret"));
    RestClient client(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("no acceptable authentication method"),
                  std::string::npos)
            << e.what();
        EXPECT_EQ(e.transport_error(), boost::asio::error::access_denied);
    }
}

TEST(SocksRest, AMethodThatWasNotOfferedIsRefused) {
    MockServer server;
    MockSocks socks(socks_method_reply(1)); // GSSAPI
    RestClient client(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("not offered"), std::string::npos) << e.what();
    }
}

TEST(SocksRest, FailureRepliesMapToTransportErrors) {
    struct Case {
        std::uint8_t reply;
        boost::system::error_code code;
        const char* text;
    };
    const Case cases[] = {
        {1, boost::asio::error::connection_aborted, "general failure"},
        {2, boost::asio::error::no_permission, "ruleset"},
        {3, boost::asio::error::network_unreachable, "network unreachable"},
        {4, boost::asio::error::host_unreachable, "host unreachable"},
        {5, boost::asio::error::connection_refused, "refused the connection"},
        {6, boost::asio::error::timed_out, "TTL expired"},
        {7, boost::asio::error::operation_not_supported, "command not supported"},
        {8, boost::asio::error::address_family_not_supported, "address type not supported"},
        {9, make_error_code(boost::system::errc::protocol_error), "unknown failure"},
    };
    for (const auto& c : cases) {
        MockServer server;
        MockSocks socks(socks_connect_reply(c.reply));
        RestClient client(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
        try {
            (void)client.send_request(get("/x"));
            FAIL() << "expected NetworkError for reply " << static_cast<int>(c.reply);
        } catch (const NetworkError& e) {
            EXPECT_NE(std::string(e.what()).find(c.text), std::string::npos) << e.what();
            EXPECT_NE(std::string(e.what()).find("SOCKS5 proxy"), std::string::npos) << e.what();
            EXPECT_EQ(e.transport_error(), c.code) << e.what();
            EXPECT_FALSE(e.request_sent());
        }
        EXPECT_EQ(server.request_count(), 0U);
    }
}

TEST(SocksRest, ARefusedTargetBehindTheProxyIsReported) {
    MockSocks socks;
    std::string url;
    {
        MockServer gone;
        url = gone.url();
    }
    RestClient client(rest_config(url, socks_at(socks, ProxyProtocol::Socks5)));
    EXPECT_THROW((void)client.send_request(get("/x")), NetworkError);
}

TEST(SocksRest, ASilentProxyTimesOut) {
    MockServer server;
    MockSocks socks(socks_delay(1500ms));
    auto cfg = rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5));
    cfg.timeout = 200ms;
    RestClient client(std::move(cfg));
    const auto start = std::chrono::steady_clock::now();
    EXPECT_THROW((void)client.send_request(get("/x")), RequestTimeoutError);
    EXPECT_LT(std::chrono::steady_clock::now() - start, 1200ms);
}

TEST(SocksRest, AnUnreachableProxyIsANetworkError) {
    MockServer server;
    std::uint16_t port = 0;
    {
        MockSocks socks;
        port = socks.port();
    }
    RestApiConfig cfg =
        rest_config(server.url(), ProxyConfig{"127.0.0.1", port, ProxyProtocol::Socks5, {}});
    RestClient client(std::move(cfg));
    try {
        (void)client.send_request(get("/x"));
        FAIL() << "expected NetworkError";
    } catch (const NetworkError& e) {
        EXPECT_EQ(e.transport_error(), boost::asio::error::connection_refused);
    }
}

TEST(SocksRest, LongCredentialsAreRejectedAtConstruction) {
    MockServer server;
    MockSocks socks;
    EXPECT_THROW(
        RestClient(rest_config(server.url(), socks_at(socks, ProxyProtocol::Socks5,
                                                      ProxyAuth{std::string(256, 'u'), "p"}))),
        ConfigError);
}

// ==== environment ====

TEST(SocksEnvironment, ParsesSocksUrls) {
    {
        const ProxyEnv env({{"ALL_PROXY", "socks5://user:p%40ss@proxy.local:9050"}});
        const auto proxy = proxy_from_environment(true, "api.binance.com", 443);
        ASSERT_TRUE(proxy);
        EXPECT_EQ(proxy->protocol, ProxyProtocol::Socks5);
        EXPECT_EQ(proxy->host, "proxy.local");
        EXPECT_EQ(proxy->port, 9050);
        ASSERT_TRUE(proxy->auth);
        EXPECT_EQ(proxy->auth->username, "user");
        EXPECT_EQ(proxy->auth->password, "p@ss");
    }
    {
        const ProxyEnv env({{"all_proxy", "SOCKS5H://proxy.local"}});
        const auto proxy = proxy_from_environment(false, "api.binance.com", 80);
        ASSERT_TRUE(proxy);
        EXPECT_EQ(proxy->protocol, ProxyProtocol::Socks5h);
        EXPECT_EQ(proxy->port, 1080);
        EXPECT_FALSE(proxy->auth);
    }
    {
        const ProxyEnv env(
            {{"HTTPS_PROXY", "socks5h://proxy.local:1"}, {"NO_PROXY", "binance.com"}});
        EXPECT_FALSE(proxy_from_environment(true, "api.binance.com", 443));
    }
}

TEST(SocksEnvironment, RestUsesTheProxyFromTheEnvironment) {
    MockServer server;
    MockSocks socks(socks_credentials("user", "pw"));
    const auto value = "socks5h://user:pw@127.0.0.1:" + std::to_string(socks.port());
    const ProxyEnv env({{"ALL_PROXY", value.c_str()}});
    RestApiConfig cfg;
    cfg.base_path = with_localhost(server.url());
    RestClient client(std::move(cfg));
    (void)client.send_request(get("/x"));
    const auto seen = socks.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_EQ(seen[0].host, "localhost");
    EXPECT_EQ(seen[0].username, "user");
}

// ==== WebSocket API ====

TEST(SocksWebsocketApi, ConnectsAndSends) {
    MockWsServer server(echo);
    MockSocks socks;
    WebsocketApi api(api_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    api.connect();
    EXPECT_EQ(api.send_message("ping", {}).front().result, json::parse(R"({"echo":"ping"})"));
    const auto seen = socks.requests();
    ASSERT_EQ(seen.size(), 1U);
    EXPECT_EQ(seen[0].host, "127.0.0.1");
    EXPECT_EQ(seen[0].port, port_of(server.url()));
}

TEST(SocksWebsocketApi, ConnectsWithTlsAndAuthentication) {
    MockWsServer server(echo, tls_options());
    MockSocks socks(socks_credentials("user", "pw"));
    WebsocketApi api(api_config(with_localhost(server.url()),
                                socks_at(socks, ProxyProtocol::Socks5h, ProxyAuth{"user", "pw"})));
    api.connect();
    EXPECT_EQ(api.send_message("ping", {}).front().result, json::parse(R"({"echo":"ping"})"));
    const auto seen = socks.requests().at(0);
    EXPECT_EQ(seen.address_type, 3);
    EXPECT_EQ(seen.host, "localhost");
    EXPECT_EQ(seen.username, "user");
}

TEST(SocksWebsocketApi, Socks5ResolvesTheHostNameItself) {
    MockWsServer server(echo);
    MockSocks socks;
    WebsocketApi api(
        api_config(with_localhost(server.url()), socks_at(socks, ProxyProtocol::Socks5)));
    api.connect();
    const auto seen = socks.requests().at(0);
    EXPECT_TRUE(seen.address_type == 1 || seen.address_type == 4);
}

TEST(SocksWebsocketApi, WrongCredentialsFailTheConnect) {
    MockWsServer server(echo);
    MockSocks socks(socks_credentials("user", "pw"));
    WebsocketApi api(
        api_config(server.url(), socks_at(socks, ProxyProtocol::Socks5, ProxyAuth{"user", "bad"})));
    try {
        api.connect();
        FAIL() << "expected WebsocketNetworkError";
    } catch (const WebsocketNetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("authentication failed"), std::string::npos)
            << e.what();
        EXPECT_EQ(e.transport_error(), boost::asio::error::access_denied);
    }
    EXPECT_EQ(server.session_count(), 0U);
}

TEST(SocksWebsocketApi, UnsupportedMethodFailsTheConnect) {
    MockWsServer server(echo);
    MockSocks socks(socks_method_reply(0xFF));
    WebsocketApi api(api_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    EXPECT_THROW(api.connect(), WebsocketNetworkError);
}

TEST(SocksWebsocketApi, ARefusedTargetFailsTheConnect) {
    MockWsServer server(echo);
    MockSocks socks(socks_connect_reply(5));
    WebsocketApi api(api_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    try {
        api.connect();
        FAIL() << "expected WebsocketNetworkError";
    } catch (const WebsocketNetworkError& e) {
        EXPECT_NE(std::string(e.what()).find("refused the connection"), std::string::npos)
            << e.what();
        EXPECT_EQ(e.transport_error(), boost::asio::error::connection_refused);
    }
}

TEST(SocksWebsocketApi, ASilentProxyTimesOut) {
    MockWsServer server(echo);
    MockSocks socks(socks_delay(1500ms));
    auto cfg = api_config(server.url(), socks_at(socks, ProxyProtocol::Socks5));
    cfg.connect_timeout = 200ms;
    WebsocketApi api(std::move(cfg));
    const auto start = std::chrono::steady_clock::now();
    EXPECT_THROW(api.connect(), WebsocketTimeoutError);
    EXPECT_LT(std::chrono::steady_clock::now() - start, 1200ms);
}

// ==== WebSocket streams ====

TEST(SocksWebsocketStreams, Connects) {
    MockWsServer server;
    MockSocks socks;
    WebsocketStreams streams(streams_config(server.url(), socks_at(socks, ProxyProtocol::Socks5)));
    streams.connect({"btcusdt@trade"});
    EXPECT_TRUE(streams.is_connected());
    EXPECT_EQ(server.sessions().front().target, "/stream?streams=btcusdt@trade");
    EXPECT_EQ(socks.requests().size(), 1U);
}

TEST(SocksWebsocketStreams, ConnectsWithTlsThroughAuthentication) {
    MockWsServer server({}, tls_options());
    MockSocks socks(socks_credentials("user", "pw"));
    WebsocketStreams streams(
        streams_config(with_localhost(server.url()),
                       socks_at(socks, ProxyProtocol::Socks5h, ProxyAuth{"user", "pw"})));
    streams.connect();
    EXPECT_TRUE(streams.is_connected());
    EXPECT_EQ(socks.requests().at(0).host, "localhost");
}

TEST(SocksWebsocketStreams, WrongCredentialsFailTheConnect) {
    MockWsServer server;
    MockSocks socks(socks_credentials("user", "pw"));
    WebsocketStreams streams(streams_config(
        server.url(), socks_at(socks, ProxyProtocol::Socks5, ProxyAuth{"user", "bad"})));
    EXPECT_THROW(streams.connect(), WebsocketNetworkError);
}
