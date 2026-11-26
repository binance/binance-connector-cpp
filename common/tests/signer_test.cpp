//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// `SignatureGenerator`: HMAC, RSA and Ed25519.
#include <array>
#include <atomic>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <gtest/gtest.h>
#include <openssl/hmac.h>

#include <binance/common/errors.hpp>
#include <binance/common/signer.hpp>

#include "support/keys.hpp"

using binance::common::ConnectorClientError;
using binance::common::Params;
using binance::common::PrivateKey;
using binance::common::SignatureGenerator;
namespace test = binance::test;

namespace {

std::string hmac_hex(std::string_view secret, std::string_view payload) {
    std::array<unsigned char, EVP_MAX_MD_SIZE> mac{};
    unsigned int len = 0;
    HMAC(EVP_sha256(), secret.data(), static_cast<int>(secret.size()),
         reinterpret_cast<const unsigned char*>(payload.data()), payload.size(), mac.data(), &len);
    std::string out;
    constexpr const char* kHex = "0123456789abcdef";
    for (unsigned int i = 0; i < len; ++i) {
        out += kHex[mac[i] >> 4];
        out += kHex[mac[i] & 0xF];
    }
    return out;
}

SignatureGenerator hmac(std::string secret) {
    return {std::move(secret), std::nullopt, std::nullopt};
}

SignatureGenerator with_key(const test::Pkey& key) {
    return {std::nullopt, PrivateKey::from_pem(test::private_pem(key)), std::nullopt};
}

template <class F> std::string error_of(F&& f) {
    try {
        f();
    } catch (const std::exception& e) {
        return e.what();
    }
    return {};
}

const Params kAb = {{"b", 2}, {"a", 1}};
const Params kCd = {{"d", 4}, {"c", 3}};

} // namespace

TEST(SignatureGenerator, HmacSha256Signature) {
    EXPECT_EQ(hmac("test-secret").sign(kAb), hmac_hex("test-secret", "a=1&b=2"));
}

TEST(SignatureGenerator, HmacSha256SignatureWithBody) {
    EXPECT_EQ(hmac("test-secret").sign(kAb, &kCd), hmac_hex("test-secret", "a=1&b=2c=3&d=4"));
}

TEST(SignatureGenerator, KnownHmacVector) {
    // The example from the Binance API documentation.
    const Params params = {{"symbol", "LTCBTC"},   {"side", "BUY"},
                           {"type", "LIMIT"},      {"timeInForce", "GTC"},
                           {"quantity", "1"},      {"price", "0.1"},
                           {"recvWindow", "5000"}, {"timestamp", 1499827319559}};
    EXPECT_EQ(hmac("NhqPtmdSJYdKjVHjA7PZj4Mge3R5YNiP1e3UZjInClVN65XAbvqqM6A7H5fATj0j")
                  .sign_payload("symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&"
                                "price=0.1&recvWindow=5000&timestamp=1499827319559"),
              "c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71");
    EXPECT_EQ(hmac("s").sign(params).size(), 64U);
}

TEST(SignatureGenerator, RepeatedHmacSignature) {
    const auto gen = hmac("abc");
    const Params params = {{"x", "y"}};
    EXPECT_EQ(gen.sign(params), gen.sign(params));
}

TEST(SignatureGenerator, RsaSignatureVerification) {
    const auto key = test::generate_rsa();
    const auto sig = with_key(key).sign(kAb);
    EXPECT_TRUE(test::verify(key, "a=1&b=2", sig));
    EXPECT_FALSE(test::verify(key, "a=1&b=3", sig));
}

TEST(SignatureGenerator, RsaSignatureVerificationWithBody) {
    const auto key = test::generate_rsa();
    EXPECT_TRUE(test::verify(key, "a=1&b=2c=3&d=4", with_key(key).sign(kAb, &kCd)));
}

TEST(SignatureGenerator, RepeatedRsaSignature) {
    const auto key = test::generate_rsa();
    const auto gen = with_key(key);
    const Params params = {{"k", 5}};
    EXPECT_EQ(gen.sign(params), gen.sign(params));
}

TEST(SignatureGenerator, Ed25519SignatureVerification) {
    const auto key = test::generate_ed25519();
    const auto sig = with_key(key).sign(kAb);
    EXPECT_EQ(sig.size(), 88U); // 64 bytes, base64
    EXPECT_TRUE(test::verify(key, "a=1&b=2", sig));
}

TEST(SignatureGenerator, Ed25519SignatureVerificationWithBody) {
    const auto key = test::generate_ed25519();
    EXPECT_TRUE(test::verify(key, "a=1&b=2c=3&d=4", with_key(key).sign(kAb, &kCd)));
}

TEST(SignatureGenerator, RepeatedEd25519Signature) {
    const auto key = test::generate_ed25519();
    const auto gen = with_key(key);
    const Params params = {{"m", "n"}};
    EXPECT_EQ(gen.sign(params), gen.sign(params));
}

TEST(SignatureGenerator, EncryptedKeyWithPassphrase) {
    const auto key = test::generate_ed25519();
    const SignatureGenerator gen(std::nullopt,
                                 PrivateKey::from_pem(test::private_pem(key, "hunter2")),
                                 std::string("hunter2"));
    EXPECT_TRUE(test::verify(key, "a=1&b=2", gen.sign(kAb)));

    const SignatureGenerator wrong(
        std::nullopt, PrivateKey::from_pem(test::private_pem(key, "hunter2")), std::string("nope"));
    EXPECT_NE(error_of([&] {
                  (void)wrong.sign(kAb);
              }).find("Failed to parse private key with passphrase"),
              std::string::npos);

    // An encrypted key without a passphrase must fail instead of prompting on the terminal.
    const SignatureGenerator none(
        std::nullopt, PrivateKey::from_pem(test::private_pem(key, "hunter2")), std::nullopt);
    EXPECT_NE(error_of([&] {
                  (void)none.sign(kAb);
              }).find("private key is encrypted; set private_key_passphrase"),
              std::string::npos);
}

TEST(SignatureGenerator, IndentedPemText) {
    const auto key = test::generate_ed25519();
    std::string indented;
    std::istringstream lines(test::private_pem(key));
    for (std::string line; std::getline(lines, line);) {
        indented += "        " + line + " \r\n";
    }
    const SignatureGenerator gen(std::nullopt, PrivateKey::from_pem("\n" + indented + "    "),
                                 std::nullopt);
    EXPECT_TRUE(test::verify(key, "a=1&b=2", gen.sign(kAb)));
}

TEST(SignatureGenerator, FileBasedKey) {
    const auto key = test::generate_rsa(1024);
    const auto path = std::filesystem::temp_directory_path() /
                      ("binance-signer-test-" +
                       std::to_string(::testing::UnitTest::GetInstance()->random_seed()) + ".pem");
    {
        std::ofstream out(path, std::ios::binary);
        out << test::private_pem(key);
    }
    const SignatureGenerator gen(std::nullopt, PrivateKey::from_file(path.string()), std::nullopt);
    const auto sig = gen.sign({{"z", 9}});
    std::filesystem::remove(path);
    EXPECT_TRUE(test::verify(key, "z=9", sig));
}

TEST(SignatureGenerator, MissingKeyFile) {
    const SignatureGenerator gen(std::nullopt, PrivateKey::from_file("/definitely/not/here.pem"),
                                 std::nullopt);
    EXPECT_NE(error_of([&] { (void)gen.sign(kAb); }).find("Private key file does not exist"),
              std::string::npos);
}

TEST(SignatureGenerator, UnsupportedKeyTypeError) {
    const auto key = test::generate_ec_p256();
    const auto err = error_of([&] { (void)with_key(key).sign({{"x", "y"}}); });
    EXPECT_NE(err.find("Unsupported private key type"), std::string::npos) << err;
}

TEST(SignatureGenerator, InvalidPrivateKeyError) {
    const SignatureGenerator gen(std::nullopt, PrivateKey::from_pem("not a key"), std::nullopt);
    const auto err = error_of([&] { (void)gen.sign({{"foo", "bar"}}); });
    EXPECT_NE(err.find("Failed to parse private key"), std::string::npos) << err;
}

TEST(SignatureGenerator, MissingCredentialsError) {
    const SignatureGenerator gen(std::nullopt, std::nullopt, std::nullopt);
    const auto err = error_of([&] { (void)gen.sign({{"a", 1}}); });
    EXPECT_NE(err.find("Either 'api_secret' or 'private_key' must be provided"), std::string::npos);
    EXPECT_THROW((void)gen.sign({{"a", 1}}), ConnectorClientError);
}

TEST(SignatureGenerator, UnencodedHmacSignatureDoesNotPercentEncodeNonAscii) {
    const Params params = {{"apiKey", "key"}, {"symbol", "我踏马来了USDT"}, {"timestamp", 1}};
    const auto gen = hmac("test-secret");
    const auto sig = gen.sign_unencoded(params);
    EXPECT_EQ(sig, hmac_hex("test-secret", "apiKey=key&symbol=我踏马来了USDT&timestamp=1"));
    EXPECT_NE(sig, gen.sign(params));
}

TEST(SignatureGenerator, UnencodedEd25519SignatureDoesNotPercentEncodeNonAscii) {
    const auto key = test::generate_ed25519();
    const Params params = {{"apiKey", "key"}, {"symbol", "我踏马来了USDT"}, {"timestamp", 1}};
    EXPECT_TRUE(test::verify(key, "apiKey=key&symbol=我踏马来了USDT&timestamp=1",
                             with_key(key).sign_unencoded(params)));
}

TEST(SignatureGenerator, ConcurrentLazyKeyLoading) {
    const auto key = test::generate_ed25519();
    const auto gen = with_key(key);
    std::vector<std::thread> threads;
    std::atomic<int> ok{0};
    for (int i = 0; i < 8; ++i) {
        threads.emplace_back([&] {
            if (test::verify(key, "a=1&b=2", gen.sign(kAb))) {
                ++ok;
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    EXPECT_EQ(ok.load(), 8);
}
