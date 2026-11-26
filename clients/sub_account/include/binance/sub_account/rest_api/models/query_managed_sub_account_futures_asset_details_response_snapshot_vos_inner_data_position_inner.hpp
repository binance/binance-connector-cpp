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

#include <binance/common/decimal.hpp>
#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner {
    std::optional<std::string> symbol;
    std::optional<std::int64_t> entry_price;
    std::optional<std::int64_t> mark_price;
    std::optional<common::Decimal> position_amt;

    bool operator==(
        const QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT
QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner tag_invoke(
    boost::json::value_to_tag<
        QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner> /*tag*/
    ,
    const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(
    boost::json::value_from_tag /*tag*/, boost::json::value& jv,
    const QueryManagedSubAccountFuturesAssetDetailsResponseSnapshotVosInnerDataPositionInner& v);

} // namespace binance::sub_account::rest_api
