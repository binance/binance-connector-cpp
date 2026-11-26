//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

// `build_query_string` and `build_plain_query_string`.
#include <boost/json/parse.hpp>
#include <gtest/gtest.h>

#include <binance/common/detail/utils.hpp>
#include <binance/common/errors.hpp>

#include "utils.hpp"

using binance::common::ConnectorClientError;
using binance::common::Params;
using binance::common::detail::build_plain_query_string;
using binance::common::detail::build_query_string;

namespace {

boost::json::value j(std::string_view text) {
    return boost::json::parse(text);
}

std::string plain_error(const Params& params) {
    try {
        (void)build_plain_query_string(params);
    } catch (const ConnectorClientError& e) {
        return e.what();
    }
    return {};
}

} // namespace

TEST(BuildQueryString, EmptyMapReturnsEmptyString) {
    EXPECT_EQ(build_query_string({}), "");
}

TEST(BuildQueryString, StringAndNumberAndBool) {
    EXPECT_EQ(build_query_string({{"foo", "bar"}, {"num", 42}, {"flag", true}}),
              "flag=true&foo=bar&num=42");
}

TEST(BuildQueryString, NullIsSkipped) {
    EXPECT_EQ(build_query_string({{"a", true}, {"b", nullptr}}), "a=true");
}

TEST(BuildQueryString, PercentEncodeSpecialChars) {
    EXPECT_EQ(build_query_string({{"space", "hello world"}, {"symbols", "a/b?c"}}),
              "space=hello+world&symbols=a%2Fb%3Fc");
}

TEST(BuildQueryString, PrimitiveArrayJsonEncoded) {
    EXPECT_EQ(
        build_query_string({{"strs", j(R"(["a","b","c"])")},
                            {"nums", j("[1,2,3]")},
                            {"bools", j("[true,false]")}}),
        "bools=%5Btrue%2Cfalse%5D&nums=%5B1%2C2%2C3%5D&strs=%5B%22a%22%2C%22b%22%2C%22c%22%5D");
}

TEST(BuildQueryString, NestedArrayJsonEncoded) {
    EXPECT_EQ(build_query_string({{"nested", j("[[1,2],[3,4]]")}}),
              "nested=%5B%5B1%2C2%5D%2C%5B3%2C4%5D%5D");
}

TEST(BuildQueryString, ObjectJsonEncoded) {
    EXPECT_EQ(build_query_string({{"obj", j(R"({"k":1,"v":"two"})")}}),
              "obj=%7B%22k%22%3A1%2C%22v%22%3A%22two%22%7D");
}

TEST(BuildQueryString, EmptyArray) {
    EXPECT_EQ(build_query_string({{"foo", j("[]")}}), "foo=%5B%5D");
}

TEST(BuildQueryString, MixedArray) {
    EXPECT_EQ(build_query_string({{"mix", j(R"([1,"x",false])")}}),
              "mix=%5B1%2C%22x%22%2Cfalse%5D");
}

TEST(BuildQueryString, ArrayOfObjects) {
    EXPECT_EQ(build_query_string({{"objs", j(R"([{"a":1},{"b":2}])")}}),
              "objs=%5B%7B%22a%22%3A1%7D%2C%7B%22b%22%3A2%7D%5D");
}

TEST(BuildQueryString, EmptyObject) {
    EXPECT_EQ(build_query_string({{"emp", j("{}")}}), "emp=%7B%7D");
}

TEST(BuildQueryString, FloatsAndNegatives) {
    EXPECT_EQ(build_query_string({{"fl", 1.23456}, {"neg", -0.001}}), "fl=1.23456&neg=-0.001");
}

TEST(BuildQueryString, LargeIntegersKeepPrecision) {
    EXPECT_EQ(build_query_string({{"id", j("18446744073709551615")}, {"n", INT64_MIN}}),
              "id=18446744073709551615&n=-9223372036854775808");
}

TEST(BuildQueryString, UnicodeAndSpecialKey) {
    EXPECT_EQ(build_query_string({{"こんにちは", "世界"}, {"weird key/?=", "val"}}),
              "weird+key%2F%3F%3D=val&%E3%81%93%E3%82%93%E3%81%AB%E3%81%A1%E3%81%AF="
              "%E4%B8%96%E7%95%8C");
}

TEST(BuildQueryString, EmptyStringValue) {
    EXPECT_EQ(build_query_string({{"empty", ""}}), "empty=");
}

TEST(BuildQueryString, NullsInArray) {
    EXPECT_EQ(build_query_string({{"a", j(R"([null,1,"x"])")}}), "a=%5Bnull%2C1%2C%22x%22%5D");
}

TEST(BuildQueryString, SpecialCharsInKey) {
    EXPECT_EQ(build_query_string({{"a=b&c%", "val"}}), "a%3Db%26c%25=val");
}

TEST(BuildQueryString, EmptyKey) {
    EXPECT_EQ(build_query_string({{"", "v"}}), "=v");
}

TEST(BuildPlainQueryString, EmptyMapReturnsEmptyString) {
    EXPECT_EQ(build_plain_query_string({}), "");
}

TEST(BuildPlainQueryString, StringAndNumberAndBoolAreNotPercentEncoded) {
    EXPECT_EQ(build_plain_query_string({{"foo", "bar"}, {"num", 42}, {"flag", true}}),
              "flag=true&foo=bar&num=42");
}

TEST(BuildPlainQueryString, NullIsSkipped) {
    EXPECT_EQ(build_plain_query_string({{"a", true}, {"b", nullptr}}), "a=true");
}

TEST(BuildPlainQueryString, NonAsciiValuesAreKeptRaw) {
    EXPECT_EQ(build_plain_query_string({{"symbol", "我踏马来了USDT"}}), "symbol=我踏马来了USDT");
}

TEST(BuildPlainQueryString, UnsafeCharactersAreRejected) {
    EXPECT_NE(plain_error({{"a", "1&b=2"}}).find("unsafe character"), std::string::npos);
    EXPECT_NE(plain_error({{"a", "1=2"}}).find("unsafe character"), std::string::npos);
    EXPECT_NE(plain_error({{"a", "line1\nline2"}}).find("unsafe character"), std::string::npos);
    EXPECT_NE(plain_error({{"a&b", "v"}}).find("unsafe character"), std::string::npos);
}

TEST(BuildPlainQueryString, AmbiguousParameterSetsNoLongerCollide) {
    EXPECT_THROW((void)build_plain_query_string({{"a", "1&b=2"}}), ConnectorClientError);
    EXPECT_EQ(build_plain_query_string({{"a", "1"}, {"b", "2"}}), "a=1&b=2");
}
