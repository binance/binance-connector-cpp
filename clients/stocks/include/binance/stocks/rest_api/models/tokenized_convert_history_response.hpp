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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/stocks/export.hpp>
#include <binance/stocks/rest_api/models/tokenized_convert_history_response_rows_inner.hpp>

namespace binance::stocks::rest_api {

struct TokenizedConvertHistoryResponse {
    /// Convert history rows on this page. Empty array if nothing matches.
    std::optional<std::vector<TokenizedConvertHistoryResponseRowsInner>> rows;
    /// `true` when more pages exist — pass `nextLastId` as `lastId` on the next request.
    std::optional<bool> has_more;
    /// Pass this value as `lastId` on the next request to get the following page.
    std::optional<std::int64_t> next_last_id;

    bool operator==(const TokenizedConvertHistoryResponse& /*other*/) const = default;
};

BINANCE_STOCKS_EXPORT TokenizedConvertHistoryResponse
tag_invoke(boost::json::value_to_tag<TokenizedConvertHistoryResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_STOCKS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const TokenizedConvertHistoryResponse& v);

} // namespace binance::stocks::rest_api
