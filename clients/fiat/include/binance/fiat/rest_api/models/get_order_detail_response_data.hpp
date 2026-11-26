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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/fiat/export.hpp>

namespace binance::fiat::rest_api {

struct GetOrderDetailResponseData {
    /// Order id
    std::optional<std::string> order_id;
    /// Order status
    std::optional<std::string> order_status;
    /// Order amount
    std::optional<std::string> amount;
    /// Trade fee
    std::optional<std::string> fee;
    /// Fiat token
    std::optional<std::string> fiat_currency;
    /// Error code if any
    std::optional<std::string> error_code;
    /// Error message if any
    std::optional<std::string> error_message;
    /// Extra info
    std::optional<boost::json::value> ext;

    bool operator==(const GetOrderDetailResponseData& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT GetOrderDetailResponseData tag_invoke(
    boost::json::value_to_tag<GetOrderDetailResponseData> /*tag*/, const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetOrderDetailResponseData& v);

} // namespace binance::fiat::rest_api
