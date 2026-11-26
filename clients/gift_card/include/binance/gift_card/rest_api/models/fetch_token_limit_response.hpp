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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/gift_card/export.hpp>
#include <binance/gift_card/rest_api/models/fetch_token_limit_response_data_inner.hpp>

namespace binance::gift_card::rest_api {

struct FetchTokenLimitResponse {
    std::optional<std::string> code;
    std::optional<std::string> message;
    std::optional<std::vector<FetchTokenLimitResponseDataInner>> data;
    std::optional<bool> success;

    bool operator==(const FetchTokenLimitResponse& /*other*/) const = default;
};

BINANCE_GIFT_CARD_EXPORT FetchTokenLimitResponse tag_invoke(
    boost::json::value_to_tag<FetchTokenLimitResponse> /*tag*/, const boost::json::value& jv);
BINANCE_GIFT_CARD_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                         boost::json::value& jv, const FetchTokenLimitResponse& v);

} // namespace binance::gift_card::rest_api
