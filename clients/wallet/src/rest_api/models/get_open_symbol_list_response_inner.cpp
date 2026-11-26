//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/get_open_symbol_list_response_inner.hpp>

namespace binance::wallet::rest_api {

GetOpenSymbolListResponseInner
tag_invoke(boost::json::value_to_tag<GetOpenSymbolListResponseInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "GetOpenSymbolListResponseInner");
    GetOpenSymbolListResponseInner out;
    common::detail::json::read(obj, "openTime", out.open_time);
    common::detail::json::read(obj, "symbols", out.symbols);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetOpenSymbolListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "openTime", v.open_time);
    common::detail::json::write(obj, "symbols", v.symbols);
}

} // namespace binance::wallet::rest_api
