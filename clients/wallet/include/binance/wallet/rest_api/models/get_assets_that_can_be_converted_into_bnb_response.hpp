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

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response_details_inner.hpp>

namespace binance::wallet::rest_api {

struct GetAssetsThatCanBeConvertedIntoBnbResponse {
    std::optional<std::vector<GetAssetsThatCanBeConvertedIntoBnbResponseDetailsInner>> details;
    std::optional<std::string> total_transfer_btc;
    std::optional<std::string> total_transfer_bnb;
    /// Commission fee
    std::optional<std::string> dribblet_percentage;

    bool operator==(const GetAssetsThatCanBeConvertedIntoBnbResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetAssetsThatCanBeConvertedIntoBnbResponse
tag_invoke(boost::json::value_to_tag<GetAssetsThatCanBeConvertedIntoBnbResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetAssetsThatCanBeConvertedIntoBnbResponse& v);

} // namespace binance::wallet::rest_api
