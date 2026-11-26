//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <clocale>
#include <cmath>
#include <cstdint>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/json.hpp>
#include <gtest/gtest.h>

#include <binance/common/decimal.hpp>
#include <binance/common/json.hpp>
#include <binance/common/models.hpp>

using binance::common::Decimal;

TEST(Decimal, DefaultsToZero) {
    EXPECT_EQ(Decimal().str(), "0");
}

TEST(Decimal, CanonicalisesStrings) {
    EXPECT_EQ(Decimal("0010.500").str(), "10.5");
    EXPECT_EQ(Decimal("-0.000").str(), "0");
    EXPECT_EQ(Decimal("+1.0").str(), "1");
    EXPECT_EQ(Decimal(".5").str(), "0.5");
    EXPECT_EQ(Decimal("0.00000001").str(), "0.00000001");
    EXPECT_EQ(Decimal("123456789012345678901234567890.123456789").str(),
              "123456789012345678901234567890.123456789");
}

TEST(Decimal, ExpandsExponents) {
    EXPECT_EQ(Decimal("1e-8").str(), "0.00000001");
    EXPECT_EQ(Decimal("1.5E3").str(), "1500");
    EXPECT_EQ(Decimal("-2.5e-2").str(), "-0.025");
}

TEST(Decimal, RejectsInvalidInput) {
    for (const char* bad :
         {"", "abc", "1.2.3", "1e", "--1", "1e5000", " 1", "0x10", "1e+-5", "1e-+5", "."}) {
        EXPECT_THROW((void)Decimal{std::string_view(bad)}, std::invalid_argument) << bad;
    }
}

TEST(Decimal, FromNumbers) {
    EXPECT_EQ(Decimal(0.1).str(), "0.1");
    EXPECT_EQ(Decimal(1e-7).str(), "0.0000001");
    EXPECT_EQ(Decimal(42).str(), "42");
    EXPECT_EQ(Decimal(-7LL).str(), "-7");
    EXPECT_THROW((void)Decimal{std::numeric_limits<double>::quiet_NaN()}, std::invalid_argument);
    EXPECT_THROW((void)Decimal{std::numeric_limits<double>::infinity()}, std::invalid_argument);
}

TEST(Decimal, FromDoublesUsesShortestRoundTripText) {
    EXPECT_EQ(Decimal(-0.0).str(), "0");
    EXPECT_EQ(Decimal(1.5e300).str(), "15" + std::string(299, '0'));
    EXPECT_EQ(Decimal(5e-324).str(), "0." + std::string(323, '0') + "5");
    EXPECT_EQ(Decimal(123456789012345.67).str(), "123456789012345.67");
    // From 2^53 up, all exact digits when they are no longer than the exponent form.
    EXPECT_EQ(Decimal(1e23).str(), "100000000000000000000000");
    EXPECT_EQ(Decimal(-218470626061754144.0).str(), "-218470626061754144");
    EXPECT_EQ(Decimal(9007199254740993.0).str(), "9007199254740992");
}

TEST(Decimal, RejectsFloatAndNullPointer) {
    static_assert(!std::is_constructible_v<Decimal, float>);
    static_assert(std::is_constructible_v<Decimal, double>);
    static_assert(std::is_constructible_v<Decimal, long double>);
    const char* null = nullptr;
    EXPECT_THROW((void)Decimal(null), std::invalid_argument);
}

TEST(Decimal, ToDoubleRoundsCorrectly) {
    EXPECT_EQ(Decimal("0.1").to_double(), 0.1);
    EXPECT_EQ(Decimal("-1e-7").to_double(), -1e-7);
    EXPECT_EQ(Decimal("18446744073709551615").to_double(), 18446744073709551615.0);
    EXPECT_EQ(Decimal("-9223372036854775808").to_double(), -9223372036854775808.0);
    EXPECT_EQ(Decimal("123456789012345678901234567890").to_double(), 1.2345678901234568e29);
    EXPECT_EQ(Decimal("2.4703282292062328e-324").to_double(), 5e-324); // just above the midpoint
    EXPECT_EQ(Decimal("2.4703282292062327e-324").to_double(), 0.0);    // just below it
    EXPECT_EQ(Decimal("1.7976931348623157e308").to_double(), std::numeric_limits<double>::max());
}

TEST(Decimal, ToDoubleIgnoresTheLocale) {
    // A locale with `,` as the decimal separator, when the system has one.
    const std::string previous = std::setlocale(LC_ALL, nullptr);
    bool set = false;
    for (const char* name : {"de_DE.UTF-8", "de_DE.utf8", "fr_FR.UTF-8", "fr_FR.utf8", "de_DE"}) {
        if (std::setlocale(LC_ALL, name) != nullptr) {
            set = true;
            break;
        }
    }
    const double parsed = Decimal("1234.5").to_double();
    const auto text = Decimal(0.25).str();
    std::setlocale(LC_ALL, previous.c_str());
    if (!set) {
        GTEST_SKIP() << "no locale with a comma decimal separator";
    }
    EXPECT_EQ(parsed, 1234.5);
    EXPECT_EQ(text, "0.25");
}

TEST(Decimal, ComparesCanonicalForm) {
    EXPECT_EQ(Decimal("1.50"), Decimal("1.5"));
    EXPECT_NE(Decimal("1.5"), Decimal("1.51"));
    EXPECT_DOUBLE_EQ(Decimal("2.25").to_double(), 2.25);
}

TEST(Decimal, OrdersNumerically) {
    const std::vector<Decimal> ascending = {
        Decimal("-100"),   Decimal("-9.5"),  Decimal("-0.12"), Decimal("-0.1"), Decimal("0"),
        Decimal("0.0001"), Decimal("0.1"),   Decimal("0.12"),  Decimal("0.2"),  Decimal("9.99"),
        Decimal("10"),     Decimal("10.01"), Decimal("100")};
    for (std::size_t i = 0; i < ascending.size(); ++i) {
        for (std::size_t j = 0; j < ascending.size(); ++j) {
            EXPECT_EQ(ascending[i] <=> ascending[j], i <=> j)
                << ascending[i] << " vs " << ascending[j];
        }
    }
}

TEST(Decimal, MovedFromIsZero) {
    Decimal a("1.5");
    Decimal b(std::move(a));
    EXPECT_EQ(b.str(), "1.5");
    EXPECT_EQ(a.str(), "0"); // NOLINT(bugprone-use-after-move)

    Decimal c("2.5");
    c = std::move(b);
    EXPECT_EQ(c.str(), "1.5");
    EXPECT_EQ(b.str(), "0"); // NOLINT(bugprone-use-after-move)
}

TEST(Decimal, SelfMoveAssignmentKeepsTheValue) {
    Decimal a("1.5");
    auto& alias = a;
    a = std::move(alias);
    EXPECT_EQ(a.str(), "1.5"); // NOLINT(bugprone-use-after-move)
}

TEST(Decimal, ToDoubleSaturatesOutOfRange) {
    EXPECT_EQ(Decimal("1e400").to_double(), HUGE_VAL);
    EXPECT_EQ(Decimal("-1e400").to_double(), -HUGE_VAL);
    EXPECT_EQ(Decimal("1e-400").to_double(), 0.0);
    EXPECT_TRUE(std::signbit(Decimal("-1e-400").to_double()));
}

TEST(Decimal, IntegralConstructorExcludesBoolAndCharacters) {
    static_assert(std::is_constructible_v<Decimal, int>);
    static_assert(std::is_constructible_v<Decimal, std::uint64_t>);
    static_assert(!std::is_constructible_v<Decimal, bool>);
    static_assert(!std::is_constructible_v<Decimal, char>);
}

TEST(Decimal, JsonRoundTrip) {
    EXPECT_EQ(boost::json::value_from(Decimal("0.1")), boost::json::value("0.1"));
    EXPECT_EQ(boost::json::value_to<Decimal>(boost::json::value("1.000")), Decimal("1"));
    EXPECT_EQ(boost::json::value_to<Decimal>(boost::json::value(12)), Decimal("12"));
    EXPECT_EQ(boost::json::value_to<Decimal>(boost::json::value(0.25)), Decimal("0.25"));
    EXPECT_ANY_THROW(boost::json::value_to<Decimal>(boost::json::value(true)));
    // JSON numbers other than 64-bit integers go through a double.
    const auto jv = binance::common::parse_json(
        R"([18446744073709551615, -9223372036854775808, 0.12345678901234567890123, 1e-7])");
    EXPECT_EQ(boost::json::value_to<Decimal>(jv.at(0)).str(), "18446744073709551615");
    EXPECT_EQ(boost::json::value_to<Decimal>(jv.at(1)).str(), "-9223372036854775808");
    EXPECT_EQ(boost::json::value_to<Decimal>(jv.at(2)).str(), "0.12345678901234568");
    EXPECT_EQ(boost::json::value_to<Decimal>(jv.at(3)).str(), "0.0000001");
}

TEST(Decimal, Streams) {
    std::ostringstream os;
    os << Decimal("3.140");
    EXPECT_EQ(os.str(), "3.14");
}

TEST(Json, ToJsonGivesTheJsonOfAValue) {
    EXPECT_EQ(binance::common::to_json(Decimal("0.10")), R"("0.1")");
    EXPECT_EQ(binance::common::to_json(std::vector<Decimal>{Decimal("1"), Decimal("2.5")}),
              R"(["1","2.5"])");
    binance::common::RestApiRateLimit limit;
    limit.interval_num = 1;
    limit.count = 7;
    const auto text = binance::common::to_json(std::vector{limit});
    EXPECT_EQ(text.front(), '[');
    EXPECT_NE(text.find(R"("rateLimitType":"REQUEST_WEIGHT")"), std::string::npos) << text;
    EXPECT_NE(text.find(R"("count":7)"), std::string::npos) << text;
}
