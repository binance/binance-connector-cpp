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

#include <binance/staking/export.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner_detail.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner_quota.hpp>

namespace binance::staking::rest_api {

struct GetOnChainYieldsLockedProductListResponseRowsInner {
    std::optional<std::string> project_id;
    std::optional<GetOnChainYieldsLockedProductListResponseRowsInnerDetail> detail;
    std::optional<GetOnChainYieldsLockedProductListResponseRowsInnerQuota> quota;

    bool
    operator==(const GetOnChainYieldsLockedProductListResponseRowsInner& /*other*/) const = default;
};

BINANCE_STAKING_EXPORT GetOnChainYieldsLockedProductListResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetOnChainYieldsLockedProductListResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_STAKING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                       const GetOnChainYieldsLockedProductListResponseRowsInner& v);

} // namespace binance::staking::rest_api
