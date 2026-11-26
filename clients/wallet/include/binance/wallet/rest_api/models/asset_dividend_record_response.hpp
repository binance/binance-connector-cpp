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
#include <binance/wallet/rest_api/models/asset_dividend_record_response_rows_inner.hpp>

namespace binance::wallet::rest_api {

struct AssetDividendRecordResponse {
    std::optional<std::vector<AssetDividendRecordResponseRowsInner>> rows;
    std::optional<std::int64_t> total;

    bool operator==(const AssetDividendRecordResponse& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT AssetDividendRecordResponse tag_invoke(
    boost::json::value_to_tag<AssetDividendRecordResponse> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AssetDividendRecordResponse& v);

} // namespace binance::wallet::rest_api
