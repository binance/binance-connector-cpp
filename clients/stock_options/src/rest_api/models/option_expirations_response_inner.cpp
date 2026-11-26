//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stock_options/rest_api/models/option_expirations_response_inner.hpp>

namespace binance::stock_options::rest_api {

OptionExpirationsResponseInner
tag_invoke(boost::json::value_to_tag<OptionExpirationsResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "OptionExpirationsResponseInner");
    OptionExpirationsResponseInner out;
    common::detail::json::read(obj, "expirationDate", out.expiration_date);
    common::detail::json::read(obj, "rootSymbol", out.root_symbol);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const OptionExpirationsResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "expirationDate", v.expiration_date);
    common::detail::json::write(obj, "rootSymbol", v.root_symbol);
}

} // namespace binance::stock_options::rest_api
