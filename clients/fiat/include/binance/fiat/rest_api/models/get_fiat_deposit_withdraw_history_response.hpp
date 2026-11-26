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
#include <binance/fiat/rest_api/models/get_fiat_deposit_withdraw_history_response_data_inner.hpp>

namespace binance::fiat::rest_api {

struct GetFiatDepositWithdrawHistoryResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::vector<GetFiatDepositWithdrawHistoryResponseDataInner>> data;
    std::optional<std::int64_t> total;
    std::optional<bool> success;

    bool operator==(const GetFiatDepositWithdrawHistoryResponse& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT GetFiatDepositWithdrawHistoryResponse
tag_invoke(boost::json::value_to_tag<GetFiatDepositWithdrawHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const GetFiatDepositWithdrawHistoryResponse& v);

} // namespace binance::fiat::rest_api
