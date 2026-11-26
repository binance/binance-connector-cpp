//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/margin_trading/websocket_streams/models/user_liability_change.hpp>

namespace binance::margin_trading::websocket_streams {

UserLiabilityChange tag_invoke(boost::json::value_to_tag<UserLiabilityChange> /*tag*/,
                               const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "UserLiabilityChange");
    UserLiabilityChange out;
    common::detail::json::read(obj, "E", out.e_uppercase);
    common::detail::json::read(obj, "a", out.a);
    common::detail::json::read(obj, "t", out.t);
    common::detail::json::read(obj, "p", out.p);
    common::detail::json::read(obj, "i", out.i);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const UserLiabilityChange& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "E", v.e_uppercase);
    common::detail::json::write(obj, "a", v.a);
    common::detail::json::write(obj, "t", v.t);
    common::detail::json::write(obj, "p", v.p);
    common::detail::json::write(obj, "i", v.i);
}

} // namespace binance::margin_trading::websocket_streams
