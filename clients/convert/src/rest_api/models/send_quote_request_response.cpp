//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/convert/rest_api/models/send_quote_request_response.hpp>

namespace binance::convert::rest_api {

SendQuoteRequestResponse tag_invoke(boost::json::value_to_tag<SendQuoteRequestResponse> /*tag*/,
                                    const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "SendQuoteRequestResponse");
    SendQuoteRequestResponse out;
    common::detail::json::read(obj, "quoteId", out.quote_id);
    common::detail::json::read(obj, "ratio", out.ratio);
    common::detail::json::read(obj, "inverseRatio", out.inverse_ratio);
    common::detail::json::read(obj, "validTimestamp", out.valid_timestamp);
    common::detail::json::read(obj, "toAmount", out.to_amount);
    common::detail::json::read(obj, "fromAmount", out.from_amount);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const SendQuoteRequestResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "quoteId", v.quote_id);
    common::detail::json::write(obj, "ratio", v.ratio);
    common::detail::json::write(obj, "inverseRatio", v.inverse_ratio);
    common::detail::json::write(obj, "validTimestamp", v.valid_timestamp);
    common::detail::json::write(obj, "toAmount", v.to_amount);
    common::detail::json::write(obj, "fromAmount", v.from_amount);
}

} // namespace binance::convert::rest_api
