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

#include <binance/w3w_prediction/export.hpp>

namespace binance::w3w_prediction::rest_api {

struct QueryTransferStatusResponse {
    std::optional<std::string> transfer_id;
    std::optional<std::string> direction;
    std::optional<std::string> status;
    std::optional<std::string> from_token;
    std::optional<std::string> from_token_amount;
    std::optional<std::string> to_token;
    std::optional<std::string> to_token_amount;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> error_code;
    /// `std::nullopt` when the field is absent; holds `std::nullopt` when it is `null`.
    std::optional<std::optional<std::string>> error_message;
    std::optional<std::string> create_time;
    std::optional<std::string> update_time;

    bool operator==(const QueryTransferStatusResponse& /*other*/) const = default;
};

BINANCE_W3W_PREDICTION_EXPORT QueryTransferStatusResponse tag_invoke(
    boost::json::value_to_tag<QueryTransferStatusResponse> /*tag*/, const boost::json::value& jv);
BINANCE_W3W_PREDICTION_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                              boost::json::value& jv,
                                              const QueryTransferStatusResponse& v);

} // namespace binance::w3w_prediction::rest_api
