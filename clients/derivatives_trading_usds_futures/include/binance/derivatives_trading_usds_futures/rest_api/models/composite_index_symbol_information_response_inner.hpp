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

#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/composite_index_symbol_information_response_inner_base_asset_list_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct CompositeIndexSymbolInformationResponseInner {
    std::optional<std::string> symbol;
    /// Current time
    std::optional<std::int64_t> time;
    /// Component asset
    std::optional<std::string> component;
    std::optional<std::vector<CompositeIndexSymbolInformationResponseInnerBaseAssetListInner>>
        base_asset_list;

    bool operator==(const CompositeIndexSymbolInformationResponseInner& /*other*/) const = default;
};

BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT CompositeIndexSymbolInformationResponseInner
tag_invoke(boost::json::value_to_tag<CompositeIndexSymbolInformationResponseInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const CompositeIndexSymbolInformationResponseInner& v);

} // namespace binance::derivatives_trading_usds_futures::rest_api
