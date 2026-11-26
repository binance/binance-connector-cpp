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

struct QueryUserUniversalTransferHistoryResponseRowsInner {
    std::optional<std::string> asset;
    std::optional<std::string> amount;
    std::optional<std::string> type;
    /// status: CONFIRMED / FAILED / PENDING
    std::optional<std::string> status;
    std::optional<std::int64_t> tran_id;
    std::optional<std::int64_t> timestamp;

    bool
    operator==(const QueryUserUniversalTransferHistoryResponseRowsInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT QueryUserUniversalTransferHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<QueryUserUniversalTransferHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const QueryUserUniversalTransferHistoryResponseRowsInner& v);

} // namespace binance::wallet::rest_api
