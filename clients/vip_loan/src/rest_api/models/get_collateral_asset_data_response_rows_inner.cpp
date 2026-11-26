//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/vip_loan/rest_api/models/get_collateral_asset_data_response_rows_inner.hpp>

namespace binance::vip_loan::rest_api {

GetCollateralAssetDataResponseRowsInner
tag_invoke(boost::json::value_to_tag<GetCollateralAssetDataResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetCollateralAssetDataResponseRowsInner");
    GetCollateralAssetDataResponseRowsInner out;
    common::detail::json::read(obj, "collateralCoin", out.collateral_coin);
    common::detail::json::read(obj, "_1stCollateralRatio", out._1st_collateral_ratio);
    common::detail::json::read(obj, "_1stCollateralRange", out._1st_collateral_range);
    common::detail::json::read(obj, "_2ndCollateralRatio", out._2nd_collateral_ratio);
    common::detail::json::read(obj, "_2ndCollateralRange", out._2nd_collateral_range);
    common::detail::json::read(obj, "_3rdCollateralRatio", out._3rd_collateral_ratio);
    common::detail::json::read(obj, "_3rdCollateralRange", out._3rd_collateral_range);
    common::detail::json::read(obj, "_4thCollateralRatio", out._4th_collateral_ratio);
    common::detail::json::read(obj, "_4thCollateralRange", out._4th_collateral_range);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetCollateralAssetDataResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "collateralCoin", v.collateral_coin);
    common::detail::json::write(obj, "_1stCollateralRatio", v._1st_collateral_ratio);
    common::detail::json::write(obj, "_1stCollateralRange", v._1st_collateral_range);
    common::detail::json::write(obj, "_2ndCollateralRatio", v._2nd_collateral_ratio);
    common::detail::json::write(obj, "_2ndCollateralRange", v._2nd_collateral_range);
    common::detail::json::write(obj, "_3rdCollateralRatio", v._3rd_collateral_ratio);
    common::detail::json::write(obj, "_3rdCollateralRange", v._3rd_collateral_range);
    common::detail::json::write(obj, "_4thCollateralRatio", v._4th_collateral_ratio);
    common::detail::json::write(obj, "_4thCollateralRange", v._4th_collateral_range);
}

} // namespace binance::vip_loan::rest_api
