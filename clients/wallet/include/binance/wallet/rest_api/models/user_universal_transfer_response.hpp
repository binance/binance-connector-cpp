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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct UserUniversalTransferResponse {
    std::optional<std::int64_t> tran_id;

    bool operator==(const UserUniversalTransferResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT UserUniversalTransferResponse tag_invoke(
    boost::json::value_to_tag<UserUniversalTransferResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const UserUniversalTransferResponse& v);

} // namespace binance::wallet::rest_api
