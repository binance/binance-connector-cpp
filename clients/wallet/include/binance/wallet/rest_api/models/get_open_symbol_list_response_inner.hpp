//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct GetOpenSymbolListResponseInner {
    std::optional<std::int64_t> open_time;
    std::optional<std::vector<std::string>> symbols;

    bool operator==(const GetOpenSymbolListResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetOpenSymbolListResponseInner
tag_invoke(boost::json::value_to_tag<GetOpenSymbolListResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetOpenSymbolListResponseInner& v);

} // namespace binance::wallet::rest_api
