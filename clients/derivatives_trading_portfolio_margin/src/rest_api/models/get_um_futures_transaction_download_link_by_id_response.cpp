//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/derivatives_trading_portfolio_margin/rest_api/models/get_um_futures_transaction_download_link_by_id_response.hpp>

namespace binance::derivatives_trading_portfolio_margin::rest_api {

GetUmFuturesTransactionDownloadLinkByIdResponse
tag_invoke(boost::json::value_to_tag<GetUmFuturesTransactionDownloadLinkByIdResponse> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "GetUmFuturesTransactionDownloadLinkByIdResponse");
    GetUmFuturesTransactionDownloadLinkByIdResponse out;
    common::detail::json::read(obj, "downloadId", out.download_id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "url", out.url);
    common::detail::json::read(obj, "s3Link", out.s3_link);
    common::detail::json::read(obj, "notified", out.notified);
    common::detail::json::read(obj, "expirationTimestamp", out.expiration_timestamp);
    common::detail::json::read(obj, "isExpired", out.is_expired);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const GetUmFuturesTransactionDownloadLinkByIdResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "downloadId", v.download_id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "url", v.url);
    common::detail::json::write(obj, "s3Link", v.s3_link);
    common::detail::json::write(obj, "notified", v.notified);
    common::detail::json::write(obj, "expirationTimestamp", v.expiration_timestamp);
    common::detail::json::write(obj, "isExpired", v.is_expired);
}

} // namespace binance::derivatives_trading_portfolio_margin::rest_api
