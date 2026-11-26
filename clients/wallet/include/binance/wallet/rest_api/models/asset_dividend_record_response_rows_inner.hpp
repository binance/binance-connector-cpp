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

struct AssetDividendRecordResponseRowsInner {
    std::optional<std::int64_t> id;
    std::optional<std::string> amount;
    std::optional<std::string> asset;
    std::optional<std::int64_t> div_time;
    std::optional<std::string> en_info;
    std::optional<std::int64_t> tran_id;
    /// direction: 1 for Asset credited (inflow), -1 for Asset debited (outflow)
    std::optional<std::int64_t> direction;

    bool operator==(const AssetDividendRecordResponseRowsInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AssetDividendRecordResponseRowsInner
tag_invoke(boost::json::value_to_tag<AssetDividendRecordResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AssetDividendRecordResponseRowsInner& v);

} // namespace binance::wallet::rest_api
