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

#include <binance/vip_loan/export.hpp>

namespace binance::vip_loan::rest_api {

struct GetCollateralAssetDataResponseRowsInner {
    std::optional<std::string> collateral_coin;
    std::optional<std::string> _1st_collateral_ratio;
    std::optional<std::string> _1st_collateral_range;
    std::optional<std::string> _2nd_collateral_ratio;
    std::optional<std::string> _2nd_collateral_range;
    std::optional<std::string> _3rd_collateral_ratio;
    std::optional<std::string> _3rd_collateral_range;
    std::optional<std::string> _4th_collateral_ratio;
    std::optional<std::string> _4th_collateral_range;

    bool operator==(const GetCollateralAssetDataResponseRowsInner& /*other*/) const = default;
};

BINANCE_VIP_LOAN_EXPORT GetCollateralAssetDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetCollateralAssetDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_VIP_LOAN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                        const GetCollateralAssetDataResponseRowsInner& v);

} // namespace binance::vip_loan::rest_api
