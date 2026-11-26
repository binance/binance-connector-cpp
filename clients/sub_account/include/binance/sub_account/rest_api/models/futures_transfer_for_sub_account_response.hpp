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

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct FuturesTransferForSubAccountResponse {
    std::optional<std::string> txn_id;

    bool operator==(const FuturesTransferForSubAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT FuturesTransferForSubAccountResponse
tag_invoke(boost::json::value_to_tag<FuturesTransferForSubAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const FuturesTransferForSubAccountResponse& v);

} // namespace binance::sub_account::rest_api
