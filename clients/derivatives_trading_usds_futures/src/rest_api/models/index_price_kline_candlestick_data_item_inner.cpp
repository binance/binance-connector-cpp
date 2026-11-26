//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <exception>
#include <string>
#include <variant>

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/index_price_kline_candlestick_data_item_inner.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

IndexPriceKlineCandlestickDataItemInner
tag_invoke(boost::json::value_to_tag<IndexPriceKlineCandlestickDataItemInner> /*tag*/,
           const boost::json::value& jv) {
    IndexPriceKlineCandlestickDataItemInner out;
    // The JSON has the shape of an alternative that does not decode: that is an error.
    std::exception_ptr failure;
    if (jv.is_int64() || jv.is_uint64()) {
        try {
            out.value = boost::json::value_to<std::int64_t>(jv);
            return out;
        } catch (const std::exception&) {
            if (!failure) {
                failure = std::current_exception();
            }
        }
    }
    if (jv.is_string()) {
        try {
            out.value = boost::json::value_to<std::string>(jv);
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
                const IndexPriceKlineCandlestickDataItemInner& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
