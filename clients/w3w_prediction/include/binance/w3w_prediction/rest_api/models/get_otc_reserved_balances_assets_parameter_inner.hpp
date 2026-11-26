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
#include <string_view>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

enum class GetOtcReservedBalancesAssetsParameterInnerTypeEnum {
    Usdt,
    Share,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_W3W_PREDICTION_EXPORT std::string_view
to_string(GetOtcReservedBalancesAssetsParameterInnerTypeEnum value) noexcept;
BINANCE_W3W_PREDICTION_EXPORT GetOtcReservedBalancesAssetsParameterInnerTypeEnum
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesAssetsParameterInnerTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           GetOtcReservedBalancesAssetsParameterInnerTypeEnum value);

struct GetOtcReservedBalancesAssetsParameterInner {
    std::optional<GetOtcReservedBalancesAssetsParameterInnerTypeEnum> type;
    std::optional<std::string> token_id;

    bool operator==(const GetOtcReservedBalancesAssetsParameterInner& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT GetOtcReservedBalancesAssetsParameterInner
tag_invoke(boost::json::value_to_tag<GetOtcReservedBalancesAssetsParameterInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const GetOtcReservedBalancesAssetsParameterInner& v);

} // namespace binance::w3w_prediction::rest_api
