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
#include <binance/wallet/rest_api/models/dust_convert_response_transfer_result_inner.hpp>

namespace binance::wallet::rest_api {

struct DustConvertResponse {
    std::optional<std::string> total_transfered;
    std::optional<std::string> total_service_charge;
    std::optional<std::vector<DustConvertResponseTransferResultInner>> transfer_result;

    bool operator==(const DustConvertResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustConvertResponse
tag_invoke(boost::json::value_to_tag<DustConvertResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustConvertResponse& v);

} // namespace binance::wallet::rest_api
