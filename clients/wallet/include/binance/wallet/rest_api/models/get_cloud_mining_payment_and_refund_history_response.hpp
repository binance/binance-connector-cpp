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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>
#include <binance/wallet/rest_api/models/get_cloud_mining_payment_and_refund_history_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

struct GetCloudMiningPaymentAndRefundHistoryResponse {
    std::optional<std::int64_t> total;
    std::optional<std::vector<GetCloudMiningPaymentAndRefundHistoryResponseRowsInner>> rows;

    bool operator==(const GetCloudMiningPaymentAndRefundHistoryResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT GetCloudMiningPaymentAndRefundHistoryResponse
tag_invoke(boost::json::value_to_tag<GetCloudMiningPaymentAndRefundHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const GetCloudMiningPaymentAndRefundHistoryResponse& v);

} // namespace binance::wallet::rest_api
