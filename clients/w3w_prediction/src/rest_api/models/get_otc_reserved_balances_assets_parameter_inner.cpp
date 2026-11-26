//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>
#include <string_view>

#include <binance/common/detail/json.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_assets_parameter_inner.hpp>

namespace binance::w3w_prediction::rest_api {

std::string_view to_string(GetOtcReservedBalancesAssetsParameterInnerTypeEnum value) noexcept {
    switch (value) {
    case GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Usdt:
        return "USDT";
    case GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Share:
        return "SHARE";
    case GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Unknown:
        break;
    }
    return "";
}

GetOtcReservedBalancesAssetsParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesAssetsParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "USDT") {
        return GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Usdt;
    }
    if (s == "SHARE") {
        return GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Share;
    }
    return GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetOtcReservedBalancesAssetsParameterInnerTypeEnum value) {
    if (value == GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Unknown) {
        throw std::invalid_argument(
            "GetOtcReservedBalancesAssetsParameterInnerTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

GetOtcReservedBalancesAssetsParameterInner
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesAssetsParameterInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetOtcReservedBalancesAssetsParameterInner");
    GetOtcReservedBalancesAssetsParameterInner out;
    common::detail::json::read(obj, "type", out.type);
    common::detail::json::read(obj, "tokenId", out.token_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOtcReservedBalancesAssetsParameterInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "type", v.type);
    common::detail::json::write(obj, "tokenId", v.token_id);
}

} // namespace binance::w3w_prediction::rest_api
