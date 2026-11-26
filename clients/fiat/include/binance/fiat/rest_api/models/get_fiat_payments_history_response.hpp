//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/fiat/export.hpp>
#include <binance/fiat/rest_api/models/get_fiat_payments_history_response_data_inner.hpp>

namespace binance::fiat::rest_api {

struct GetFiatPaymentsHistoryResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::vector<GetFiatPaymentsHistoryResponseDataInner>> data;
    std::optional<std::int64_t> total;
    std::optional<bool> success;

    bool operator==(const GetFiatPaymentsHistoryResponse& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT GetFiatPaymentsHistoryResponse
tag_invoke(boost::json::value_to_tag<GetFiatPaymentsHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetFiatPaymentsHistoryResponse& v);

} // namespace binance::fiat::rest_api
