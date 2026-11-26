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

struct GetCloudMiningPaymentAndRefundHistoryResponseRowsInner {
    std::optional<std::int64_t> create_time;
    std::optional<std::int64_t> tran_id;
    std::optional<std::int64_t> type;
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> status;

    bool operator==(const GetCloudMiningPaymentAndRefundHistoryResponseRowsInner& /*other*/) const =
        default;
};

BINANCE_WALLET_EXPORT GetCloudMiningPaymentAndRefundHistoryResponseRowsInner tag_invoke(
    boost::json::value_to_tag<GetCloudMiningPaymentAndRefundHistoryResponseRowsInner> /*tag*/,
    const boost::json::value& jv);
BINANCE_WALLET_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetCloudMiningPaymentAndRefundHistoryResponseRowsInner& v);

} // namespace binance::wallet::rest_api
