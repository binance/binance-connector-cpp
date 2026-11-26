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
#include <binance/derivatives_trading_usds_futures/rest_api/models/ticker24hr_price_change_statistics_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

Ticker24hrPriceChangeStatisticsResponse
tag_invoke(boost::json::value_to_tag<Ticker24hrPriceChangeStatisticsResponse> /*tag*/,
           const boost::json::value& jv) {
    Ticker24hrPriceChangeStatisticsResponse out;
    // The JSON has the shape of an alternative that does not decode: that is an error.
    std::exception_ptr failure;
    if (jv.is_object()) {
        try {
            out.value = boost::json::value_to<Ticker24hrPriceChangeStatisticsResponse1>(jv);
            return out;
        } catch (const std::exception&) {
            if (!failure) {
                failure = std::current_exception();
            }
        }
    }
    if (jv.is_array()) {
        try {
            out.value =
                boost::json::value_to<std::vector<Ticker24hrPriceChangeStatisticsResponse2Inner>>(
                    jv);
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
                const Ticker24hrPriceChangeStatisticsResponse& v) {
    std::visit([&jv](const auto& alternative) { jv = boost::json::value_from(alternative); },
               v.value);
}

} // namespace binance::derivatives_trading_usds_futures::rest_api
