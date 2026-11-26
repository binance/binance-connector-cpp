//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/version.hpp>

namespace binance::common {

std::string_view sdk_version() noexcept {
    return kVersion;
}

} // namespace binance::common
