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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct DustConvertResponseTransferResultInner {
    std::optional<std::int64_t> tran_id;
    std::optional<std::string> from_asset;
    std::optional<std::string> amount;
    std::optional<std::string> transfered_amount;
    std::optional<std::string> service_charge_amount;
    std::optional<std::int64_t> operate_time;

    bool operator==(const DustConvertResponseTransferResultInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DustConvertResponseTransferResultInner
tag_invoke(boost::json::value_to_tag<DustConvertResponseTransferResultInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DustConvertResponseTransferResultInner& v);

} // namespace binance::wallet::rest_api
