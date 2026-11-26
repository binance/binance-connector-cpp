//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/wallet/rest_api/models/vasp_list_response_inner.hpp>

namespace binance::wallet::rest_api {

VaspListResponseInner tag_invoke(boost::json::value_to_tag<VaspListResponseInner> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "VaspListResponseInner");
    VaspListResponseInner out;
    common::detail::json::read(obj, "vaspName", out.vasp_name);
    common::detail::json::read(obj, "vaspCode", out.vasp_code);
    common::detail::json::read(obj, "identifier", out.identifier);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const VaspListResponseInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "vaspName", v.vasp_name);
    common::detail::json::write(obj, "vaspCode", v.vasp_code);
    common::detail::json::write(obj, "identifier", v.identifier);
}

} // namespace binance::wallet::rest_api
