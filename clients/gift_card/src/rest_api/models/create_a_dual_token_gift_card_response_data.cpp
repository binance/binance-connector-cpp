//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/gift_card/rest_api/models/create_a_dual_token_gift_card_response_data.hpp>

namespace binance::gift_card::rest_api {

CreateADualTokenGiftCardResponseData
tag_invoke(boost::json::value_to_tag<CreateADualTokenGiftCardResponseData> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "CreateADualTokenGiftCardResponseData");
    CreateADualTokenGiftCardResponseData out;
    common::detail::json::read(obj, "referenceNo", out.reference_no);
    common::detail::json::read(obj, "code", out.code);
    common::detail::json::read(obj, "expiredTime", out.expired_time);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const CreateADualTokenGiftCardResponseData& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "referenceNo", v.reference_no);
    common::detail::json::write(obj, "code", v.code);
    common::detail::json::write(obj, "expiredTime", v.expired_time);
}

} // namespace binance::gift_card::rest_api
