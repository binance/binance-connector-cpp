//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

#include <boost/json/parse.hpp>
#include <gtest/gtest.h>

#include <binance/common/decimal.hpp>
#include <binance/common/detail/json.hpp>
#include <binance/common/errors.hpp>
#include <binance/common/models.hpp>
#include <binance/common/required.hpp>

namespace {

using binance::common::Decimal;
using binance::common::Params;
using binance::common::Required;

enum class Side { Buy, Sell };

struct OrderParams {
    Required<std::string> symbol;
    Required<Side> side;
    Required<std::vector<std::string>> symbols;
    std::optional<Decimal> quantity = std::nullopt;
    std::optional<std::int32_t> limit = std::nullopt;
};

static_assert(std::is_aggregate_v<OrderParams>);
static_assert(!std::is_default_constructible_v<OrderParams>);
static_assert(!std::is_default_constructible_v<Required<std::string>>);
static_assert(std::is_convertible_v<const char*, Required<std::string>>);
static_assert(!std::is_convertible_v<const char*, Required<Decimal>>);
static_assert(!std::is_convertible_v<int, Required<Side>>);

struct Fill {
    Decimal price;
    std::optional<std::vector<Decimal>> levels;
};

Fill tag_invoke(boost::json::value_to_tag<Fill> /*tag*/, const boost::json::value& jv) {
    namespace json = binance::common::detail::json;
    const auto& obj = json::as_object(jv, "Fill");
    Fill out;
    json::read(obj, "price", out.price);
    json::read(obj, "levels", out.levels);
    return out;
}

struct Order {
    std::string symbol;
    std::vector<Fill> fills;
    std::optional<std::map<std::string, std::int64_t>> counts;
};

Order tag_invoke(boost::json::value_to_tag<Order> /*tag*/, const boost::json::value& jv) {
    namespace json = binance::common::detail::json;
    const auto& obj = json::as_object(jv, "Order");
    Order out;
    json::read(obj, "symbol", out.symbol);
    json::read(obj, "fills", out.fills);
    json::read(obj, "counts", out.counts);
    return out;
}

/// The `what()` of the `ConnectorClientError` thrown by decoding `body` as `T`.
template <class T> std::string decode_error(std::string_view body) {
    const binance::common::RestApiResponse<T> response(
        binance::common::RawResponse{.status = 200, .body = std::string(body)});
    try {
        (void)response.data();
    } catch (const binance::common::ConnectorClientError& e) {
        return e.what();
    }
    return "no error";
}

TEST(Required, DesignatedInitializers) {
    const OrderParams params{
        .symbol = "BNBUSDT", .side = Side::Sell, .symbols = {"A", "B"}, .limit = 5};
    EXPECT_EQ(*params.symbol, "BNBUSDT");
    EXPECT_EQ(*params.side, Side::Sell);
    EXPECT_EQ(params.symbols->size(), 2U);
    EXPECT_FALSE(params.quantity);
    EXPECT_EQ(params.limit, 5);
}

TEST(Required, AssignsAndConverts) {
    OrderParams params{"BNBUSDT", Side::Buy, std::vector<std::string>{}};
    params.symbol = "ETHUSDT";
    params.symbols->push_back("C");
    const std::string& symbol = params.symbol;
    EXPECT_EQ(symbol, "ETHUSDT");
    EXPECT_EQ(params.symbols->front(), "C");
    EXPECT_EQ(params.symbol, Required<std::string>("ETHUSDT"));
}

TEST(Required, SetsParam) {
    const OrderParams params{.symbol = "BNBUSDT", .side = Side::Buy, .symbols = {"A"}};
    Params out;
    binance::common::detail::json::set_param(out, "symbol", params.symbol);
    binance::common::detail::json::set_param(out, "quantity", params.quantity);
    EXPECT_EQ(out.at("symbol").as_string(), "BNBUSDT");
    EXPECT_FALSE(out.contains("quantity"));
}

TEST(Required, SetsPathParamsAndHeaders) {
    namespace json = binance::common::detail::json;
    const Required<std::string> id = "a b/c";
    const Required<std::int64_t> number = 42;
    std::string endpoint = "/sapi/v1/x/{id}/y/{number}";
    json::set_path_param(endpoint, "id", id);
    json::set_path_param(endpoint, "number", number);
    EXPECT_EQ(endpoint, "/sapi/v1/x/a%20b%2Fc/y/42");

    std::vector<std::pair<std::string, std::string>> headers;
    json::set_header(headers, "lang", std::optional<std::string>("zh-CN"));
    json::set_header(headers, "unset", std::optional<std::string>());
    json::set_header(headers, "limit", Required<std::int32_t>(5));
    ASSERT_EQ(headers.size(), 2U);
    EXPECT_EQ(headers[0], (std::pair<std::string, std::string>{"lang", "zh-CN"}));
    EXPECT_EQ(headers[1], (std::pair<std::string, std::string>{"limit", "5"}));
}

TEST(Json, NullableFieldsTellNullFromMissing) {
    namespace json = binance::common::detail::json;
    const auto obj = boost::json::parse(R"({"a":null,"b":"1"})").as_object();
    std::optional<std::optional<std::string>> a;
    std::optional<std::optional<std::string>> b;
    std::optional<std::optional<std::string>> c;
    json::read(obj, "a", a);
    json::read(obj, "b", b);
    json::read(obj, "c", c);
    EXPECT_TRUE(a.has_value() && !a->has_value());
    EXPECT_EQ(b, std::optional<std::optional<std::string>>(std::string("1")));
    EXPECT_FALSE(c.has_value());

    boost::json::object out;
    json::write(out, "a", a);
    json::write(out, "b", b);
    json::write(out, "c", c);
    EXPECT_EQ(out, obj);
}

TEST(Json, DecodeErrorsNameTheFieldWithoutSourceLocations) {
    using Orders = std::vector<Order>;
    constexpr std::string_view kPrefix = "Connector client error: Failed to decode response: ";
    const auto ok = R"({"symbol":"A","fills":[{"price":"1.5","levels":[1,"2"]}],"counts":{"x":1}})";
    const binance::common::RestApiResponse<Orders> response(
        binance::common::RawResponse{.status = 200, .body = std::string("[") + ok + "]"});
    ASSERT_EQ(response.data().size(), 1U);
    EXPECT_EQ(response.data()[0].fills.at(0).levels->at(1), Decimal("2"));
    EXPECT_EQ(response.data()[0].counts->at("x"), 1);

    EXPECT_EQ(decode_error<Orders>(R"([{"symbol":"A","fills":[{"price":"1.5"},{"price":"x"}]}])"),
              std::string(kPrefix) + "field '[0].fills[1].price': Invalid decimal: 'x'");
    EXPECT_EQ(decode_error<Order>(R"({"symbol":"A","fills":[{"price":1,"levels":[1,"y"]}]})"),
              std::string(kPrefix) + "field 'fills[0].levels[1]': Invalid decimal: 'y'");
    EXPECT_EQ(decode_error<Order>(R"({"symbol":1,"fills":[]})"),
              std::string(kPrefix) + "field 'symbol': value is not a string");
    EXPECT_EQ(decode_error<Order>(R"({"symbol":"A","fills":[{}]})"),
              std::string(kPrefix) + "field 'fills[0].price': missing required field");
    EXPECT_EQ(decode_error<Order>(R"({"symbol":"A","fills":[],"counts":{"x":"1"}})"),
              std::string(kPrefix) + "field 'counts.x': not a number");
    EXPECT_EQ(decode_error<Order>(R"({"symbol":"A","fills":{}})"),
              std::string(kPrefix) + "field 'fills': expected a JSON array");
    EXPECT_EQ(decode_error<Order>(R"([])"),
              std::string(kPrefix) + "expected a JSON object for Order");
    EXPECT_EQ(decode_error<std::vector<std::string>>(R"(["a",2])"),
              std::string(kPrefix) + "field '[1]': value is not a string");
    for (const auto* body : {R"([1])", R"({"symbol":1,"fills":[]})", R"({"a":[true]})"}) {
        const auto what = decode_error<std::map<std::string, std::vector<std::string>>>(body) +
                          decode_error<Order>(body);
        EXPECT_EQ(what.find("boost.json"), std::string::npos) << what;
        EXPECT_EQ(what.find(".hpp"), std::string::npos) << what;
    }
}

TEST(Json, OneOfResultsKeepRawJsonOnlyForAnUnknownShape) {
    using Result = std::variant<Order, std::vector<Fill>, boost::json::value>;
    constexpr std::string_view kPrefix = "Connector client error: Failed to decode response: ";
    const auto decode = [](std::string_view body) {
        const binance::common::RestApiResponse<Result> response(
            binance::common::RawResponse{.status = 200, .body = std::string(body)});
        return response.data();
    };
    EXPECT_EQ(std::get<Order>(decode(R"({"symbol":"A","fills":[]})")).symbol, "A");
    EXPECT_EQ(std::get<std::vector<Fill>>(decode(R"([{"price":"2"}])")).at(0).price, Decimal("2"));
    // A shape that none of the alternatives has: kept as raw JSON.
    EXPECT_EQ(std::get<boost::json::value>(decode(R"("text")")), boost::json::value("text"));
    // The shape of an alternative that does not decode: the error says why.
    EXPECT_EQ(decode_error<Result>(R"({"symbol":1,"fills":[]})"),
              std::string(kPrefix) + "field 'symbol': value is not a string");
    EXPECT_EQ(decode_error<Result>(R"([{"price":"x"}])"),
              std::string(kPrefix) + "field '[0].price': Invalid decimal: 'x'");
}

} // namespace
