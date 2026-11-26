//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_download_id_for_um_futures_order_history_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetDownloadIdForUmFuturesOrderHistoryResponse
tag_invoke(boost::json::value_to_tag<GetDownloadIdForUmFuturesOrderHistoryResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetDownloadIdForUmFuturesOrderHistoryResponse");
    GetDownloadIdForUmFuturesOrderHistoryResponse out;
    common::detail::json::read(obj, "avgCostTimestampOfLast30d", out.avg_cost_timestamp_of_last30d);
    common::detail::json::read(obj, "downloadId", out.download_id);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetDownloadIdForUmFuturesOrderHistoryResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "avgCostTimestampOfLast30d", v.avg_cost_timestamp_of_last30d);
    common::detail::json::write(obj, "downloadId", v.download_id);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
