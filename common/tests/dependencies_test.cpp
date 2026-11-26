//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// Smoke tests proving the third-party stack resolves, links and behaves as the common library
// expects on every platform.

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/json.hpp>
#include <gtest/gtest.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <zlib.h>

TEST(Dependencies, BoostJsonKeepsFullInt64Precision) {
    boost::json::parse_options opts;
    opts.numbers = boost::json::number_precision::precise;
    auto const value =
        boost::json::parse(R"({"id":9223372036854775807,"u":18446744073709551615})", {}, opts);
    EXPECT_EQ(value.at("id").as_int64(), INT64_MAX);
    EXPECT_EQ(value.at("u").as_uint64(), UINT64_MAX);
}

TEST(Dependencies, OpenSslHmacSha256) {
    // Example from
    // https://developers.binance.com/docs/binance-spot-api-docs/rest-api/endpoint-security-type
    constexpr std::string_view key =
        "NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j";
    constexpr std::string_view payload =
        "symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&"
        "timestamp=1499827319559";

    std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
    unsigned int len = 0;
    ASSERT_NE(HMAC(EVP_sha256(), key.data(), static_cast<int>(key.size()),
                   reinterpret_cast<unsigned char const*>(payload.data()), payload.size(),
                   digest.data(), &len),
              nullptr);

    constexpr std::string_view hex = "0123456789abcdef";
    std::string out;
    for (unsigned int i = 0; i < len; ++i) {
        out += hex[digest[i] >> 4U];
        out += hex[digest[i] & 0x0FU];
    }
    EXPECT_EQ(out, "c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71");
}

TEST(Dependencies, OpenSslSupportsEd25519) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, nullptr);
    ASSERT_NE(ctx, nullptr);
    EXPECT_EQ(EVP_PKEY_keygen_init(ctx), 1);
    EVP_PKEY* key = nullptr;
    EXPECT_EQ(EVP_PKEY_keygen(ctx, &key), 1);
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(ctx);
}

TEST(Dependencies, ZlibIsLinked) {
    EXPECT_NE(std::string_view{zlibVersion()}, "");
}

TEST(Dependencies, AsioRunsHandlersAndCreatesTlsContext) {
    boost::asio::io_context io;
    boost::asio::ssl::context tls{boost::asio::ssl::context::tls_client};
    bool ran = false;
    boost::asio::post(io, [&] { ran = true; });
    io.run();
    EXPECT_TRUE(ran);
}

TEST(Dependencies, BeastRequestSerialises) {
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get,
                                                                     "/api/v3/time", 11};
    req.set(boost::beast::http::field::host, "api.binance.com");
    EXPECT_EQ(req.target(), "/api/v3/time");
}
