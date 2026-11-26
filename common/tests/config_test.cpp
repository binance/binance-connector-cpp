//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// X11 headers define `None` as a macro: the logger header must still compile, and keep it.
#define None 0L
#include <binance/common/logger.hpp>
#if !defined(None)
#error "logger.hpp must restore the None macro"
#endif
#undef None

#include <cctype>
#include <clocale>
#include <initializer_list>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include <binance/common/config.hpp>
#include <binance/common/errors.hpp>

#include "support/env.hpp"

using namespace binance::common;

TEST(RestApiConfig, Defaults) {
    const RestApiConfig cfg;
    EXPECT_EQ(cfg.timeout, std::chrono::milliseconds(1000));
    EXPECT_TRUE(cfg.keep_alive);
    EXPECT_TRUE(cfg.compression);
    EXPECT_EQ(cfg.retries, 3U);
    EXPECT_EQ(cfg.backoff, std::chrono::milliseconds(1000));
    EXPECT_TRUE(cfg.proxy_from_env);
    EXPECT_EQ(cfg.max_response_size, 128U * 1024 * 1024);
}

TEST(RestApiConfig, DebugOutputRedactsSecrets) {
    RestApiConfig cfg;
    cfg.api_key = "my-api-key";
    cfg.api_secret = "my-api-secret";
    cfg.private_key = PrivateKey::from_pem("-----BEGIN PRIVATE KEY-----secret");
    cfg.private_key_passphrase = "my-passphrase";
    cfg.proxy =
        ProxyConfig{"proxy.local", 8080, ProxyProtocol::Http, ProxyAuth{"user", "proxy-password"}};
    cfg.base_path = "https://api.binance.com";
    cfg.custom_headers = {{"Authorization", "Bearer my-token"}};

    std::ostringstream os;
    os << cfg;
    const auto out = os.str();
    for (const char* secret : {"my-api-key", "my-api-secret", "BEGIN PRIVATE KEY", "my-passphrase",
                               "proxy-password", "my-token"}) {
        EXPECT_EQ(out.find(secret), std::string::npos) << secret << " leaked: " << out;
    }
    EXPECT_NE(out.find("[REDACTED]"), std::string::npos);
    EXPECT_NE(out.find("https://api.binance.com"), std::string::npos);
    EXPECT_NE(out.find("user"), std::string::npos);
    EXPECT_NE(out.find("Authorization"), std::string::npos);
}

namespace {

using binance::test::ScopedEnv;

/// Clears every proxy variable for the test, then sets the given ones.
struct ProxyEnv {
    explicit ProxyEnv(std::initializer_list<std::pair<const char*, const char*>> vars) {
        for (const char* name :
             {"http_proxy", "HTTP_PROXY", "https_proxy", "HTTPS_PROXY", "all_proxy", "ALL_PROXY",
              "no_proxy", "NO_PROXY", "REQUEST_METHOD"}) {
            guards.push_back(std::make_unique<ScopedEnv>(name, std::nullopt));
        }
        for (const auto& [name, value] : vars) {
            guards.push_back(std::make_unique<ScopedEnv>(name, value));
        }
    }
    std::vector<std::unique_ptr<ScopedEnv>> guards;
};

} // namespace

TEST(ProxyFromEnvironment, UnsupportedSchemeIsIgnored) {
    const ProxyEnv env({{"ALL_PROXY", "socks4://127.0.0.1:1080"}});
    EXPECT_FALSE(proxy_from_environment(true, "api.binance.com", 443));
}

TEST(ProxyFromEnvironment, NoneConfigured) {
    const ProxyEnv env({});
    EXPECT_FALSE(proxy_from_environment(true, "api.binance.com", 443));
}

TEST(ProxyFromEnvironment, PicksTheVariableForTheScheme) {
    const ProxyEnv env(
        {{"HTTPS_PROXY", "https://secure.local:8443"}, {"HTTP_PROXY", "plain.local:3128"}});
    const auto tls = proxy_from_environment(true, "api.binance.com", 443);
    ASSERT_TRUE(tls);
    EXPECT_EQ(tls->protocol, ProxyProtocol::Https);
    EXPECT_EQ(tls->host, "secure.local");
    EXPECT_EQ(tls->port, 8443);
    const auto plain = proxy_from_environment(false, "api.binance.com", 80);
    ASSERT_TRUE(plain);
    EXPECT_EQ(plain->protocol, ProxyProtocol::Http);
    EXPECT_EQ(plain->host, "plain.local");
    EXPECT_EQ(plain->port, 3128);
}

TEST(ProxyFromEnvironment, LowerCaseWinsAndAllProxyIsTheFallback) {
#ifndef _WIN32 // Windows variable names are case-insensitive.
    {
        const ProxyEnv env({{"https_proxy", "http://lower:1"}, {"HTTPS_PROXY", "http://upper:2"}});
        EXPECT_EQ(proxy_from_environment(true, "h", 443)->host, "lower");
    }
#endif
    {
        const ProxyEnv env({{"ALL_PROXY", "http://everything:3"}});
        EXPECT_EQ(proxy_from_environment(true, "h", 443)->host, "everything");
    }
}

TEST(ProxyFromEnvironment, CredentialsAreDecodedAndPortsDefault) {
    const ProxyEnv env({{"https_proxy", "http://us%40er:p%3Ass@proxy.local"}});
    const auto proxy = proxy_from_environment(true, "h", 443);
    ASSERT_TRUE(proxy);
    EXPECT_EQ(proxy->port, 80);
    ASSERT_TRUE(proxy->auth);
    EXPECT_EQ(proxy->auth->username, "us@er");
    EXPECT_EQ(proxy->auth->password, "p:ss");
}

TEST(ProxyFromEnvironment, HttpProxyIsIgnoredUnderCgi) {
    const ProxyEnv env({{"HTTP_PROXY", "http://attacker:1"}, {"REQUEST_METHOD", "GET"}});
    EXPECT_FALSE(proxy_from_environment(false, "h", 80));
}

TEST(ProxyFromEnvironment, NoProxyMatching) {
    const ProxyEnv env({{"https_proxy", "http://proxy:1"},
                        {"no_proxy", " .internal , binance.com,10.0.0.1, other.com:8443"}});
    EXPECT_FALSE(proxy_from_environment(true, "api.binance.com", 443));
    EXPECT_FALSE(proxy_from_environment(true, "binance.com", 443));
    EXPECT_FALSE(proxy_from_environment(true, "x.internal", 443));
    EXPECT_FALSE(proxy_from_environment(true, "10.0.0.1", 443));
    EXPECT_FALSE(proxy_from_environment(true, "other.com", 8443));
    EXPECT_TRUE(proxy_from_environment(true, "other.com", 443));
    EXPECT_TRUE(proxy_from_environment(true, "notbinance.com", 443));
    EXPECT_TRUE(proxy_from_environment(true, "10.0.0.10", 443));
}

TEST(ProxyFromEnvironment, NoProxyIpv6Entries) {
    const ProxyEnv env({{"https_proxy", "http://proxy:1"},
                        {"no_proxy", "::1, 2001:DB8::1, [fe80::2]:443, [fe80::3]:8443"}});
    EXPECT_FALSE(proxy_from_environment(true, "::1", 443));
    EXPECT_FALSE(proxy_from_environment(true, "2001:db8::1", 443));
    EXPECT_FALSE(proxy_from_environment(true, "fe80::2", 443));
    EXPECT_TRUE(proxy_from_environment(true, "fe80::2", 8443));
    EXPECT_TRUE(proxy_from_environment(true, "fe80::3", 443));
    EXPECT_TRUE(proxy_from_environment(true, "2001:db8::2", 443));
    EXPECT_TRUE(proxy_from_environment(true, "::", 443));
}

TEST(ProxyFromEnvironment, NoProxyCaseFoldingIsAscii) {
    const std::string saved = std::setlocale(LC_ALL, nullptr);
    bool active = false;
    for (const char* name :
         {"en_US.ISO8859-1", "en_US.ISO-8859-1", "de_DE.ISO8859-1", "en_US.UTF-8", "C.UTF-8"}) {
        if (std::setlocale(LC_ALL, name) != nullptr && std::tolower(0xC9) == 0xE9) {
            active = true;
            break;
        }
    }
    if (!active) {
        std::setlocale(LC_ALL, saved.c_str());
        GTEST_SKIP() << "no locale folding non-ASCII letters";
    }
    {
        const ProxyEnv env({{"https_proxy", "http://proxy:1"}, {"no_proxy", "\xC9.example"}});
        EXPECT_TRUE(proxy_from_environment(true, "\xE9.example", 443));
    }
    std::setlocale(LC_ALL, saved.c_str());
}

TEST(ProxyFromEnvironment, NoProxyWildcard) {
    const ProxyEnv env({{"https_proxy", "http://proxy:1"}, {"NO_PROXY", "*"}});
    EXPECT_FALSE(proxy_from_environment(true, "api.binance.com", 443));
}

TEST(ProxyFromEnvironment, InvalidValueDoesNotEchoIt) {
    const ProxyEnv env({{"https_proxy", "http://user:secret-pass@host:notaport"}});
    try {
        (void)proxy_from_environment(true, "h", 443);
        FAIL() << "expected ConfigError";
    } catch (const ConfigError& e) {
        EXPECT_EQ(std::string(e.what()).find("secret-pass"), std::string::npos) << e.what();
    }
}

TEST(Logger, LevelNoneSurvivesTheX11Macro) {
    EXPECT_GT(LogLevel::None, LogLevel::Error);
}
