//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <exception>
#include <variant>

#include <binance/common/detail/json.hpp>
#include <binance/spot/websocket_api/models/ticker_book_response.hpp>

namespace binance::spot::websocket_api {

TickerBookResponse tag_invoke(boost::json::value_to_tag<TickerBookResponse> /*tag*/,
                              const boost::json::value& jv) {
    TickerBookResponse out;
    // The JSON has the shape of an alternative that does not decode: that is an error.
    std::exception_ptr failure;
    if (jv.is_object()) {
        try {
            out.value = boost::json::value_to<TickerBookResponse1>(jv);
            return out;
        } catch (const std::exception&) {
            if (!failure) {
                failure = std::current_exception();
            }
        }
    }
    if (jv.is_object()) {
        try {
            out.value = boost::json::value_to<TickerBookResponse2>(jv);
            return out;
        } catch (const std::exception&) {
            if (!failure) {
                failure = std::current_exception();
            }
        }
    }
    if (failure) {
        std::rethrow_exception(failure);
    }
    // A shape that none of the alternatives has: kept as raw JSON.
    out.value = jv;
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TickerBookResponse& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
}

} // namespace binance::spot::websocket_api
