//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <gtest/gtest.h>

#include <binance/common/version.hpp>

TEST(Version, LibraryMatchesHeaders) {
    EXPECT_EQ(binance::common::sdk_version(), binance::common::kVersion);
}
