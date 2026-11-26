//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/rest_api/models/get_all_margin_assets_response_inner.hpp>

namespace binance::margin_trading::rest_api {

GetAllMarginAssetsResponseInner
tag_invoke(boost::json::value_to_tag<GetAllMarginAssetsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetAllMarginAssetsResponseInner");
    GetAllMarginAssetsResponseInner out;
    common::detail::json::read(obj, "assetFullName", out.asset_full_name);
    common::detail::json::read(obj, "assetName", out.asset_name);
    common::detail::json::read(obj, "isBorrowable", out.is_borrowable);
    common::detail::json::read(obj, "isMortgageable", out.is_mortgageable);
    common::detail::json::read(obj, "userMinBorrow", out.user_min_borrow);
    common::detail::json::read(obj, "userMinRepay", out.user_min_repay);
    common::detail::json::read(obj, "delistTime", out.delist_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetAllMarginAssetsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "assetFullName", v.asset_full_name);
    common::detail::json::write(obj, "assetName", v.asset_name);
    common::detail::json::write(obj, "isBorrowable", v.is_borrowable);
    common::detail::json::write(obj, "isMortgageable", v.is_mortgageable);
    common::detail::json::write(obj, "userMinBorrow", v.user_min_borrow);
    common::detail::json::write(obj, "userMinRepay", v.user_min_repay);
    common::detail::json::write(obj, "delistTime", v.delist_time);
}

} // namespace binance::margin_trading::rest_api
