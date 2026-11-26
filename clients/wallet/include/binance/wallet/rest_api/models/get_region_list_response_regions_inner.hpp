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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct GetRegionListResponseRegionsInner {
    /// Region/city display name (use this value in questionnaire answers).
    std::optional<std::string> region_name;
    /// `supported`, `limited`, or `blocked`.
    std::optional<std::string> block_type;
    /// Whether deposit is allowed for this region.
    std::optional<bool> deposit_allowed;
    /// Whether withdrawal is allowed for this region.
    std::optional<bool> withdrawal_allowed;

    bool operator==(const GetRegionListResponseRegionsInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetRegionListResponseRegionsInner
tag_invoke(boost::json::value_to_tag<GetRegionListResponseRegionsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetRegionListResponseRegionsInner& v);

} // namespace binance::wallet::rest_api
