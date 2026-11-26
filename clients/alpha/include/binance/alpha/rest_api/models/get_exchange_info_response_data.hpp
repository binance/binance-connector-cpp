//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>
#include <binance/alpha/rest_api/models/get_exchange_info_response_data_assets_inner.hpp>
#include <binance/alpha/rest_api/models/get_exchange_info_response_data_symbols_inner.hpp>

namespace binance::alpha::rest_api {

/// Exchange metadata, including assets and symbols.
struct GetExchangeInfoResponseData {
    /// Timezone of market data.
    std::optional<std::string> timezone;
    /// Supported assets.
    std::optional<std::vector<GetExchangeInfoResponseDataAssetsInner>> assets;
    /// Supported trading symbols.
    std::optional<std::vector<GetExchangeInfoResponseDataSymbolsInner>> symbols;
    /// Order types metadata returned by backend.
    std::optional<std::string> order_types;

    bool operator==(const GetExchangeInfoResponseData& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT GetExchangeInfoResponseData tag_invoke(
    boost::json::value_to_tag<GetExchangeInfoResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const GetExchangeInfoResponseData& v);

} // namespace binance::alpha::rest_api
