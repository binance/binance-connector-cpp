//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/tokenized_convert_history_response_rows_inner.hpp>

namespace binance::stocks::rest_api {

TokenizedConvertHistoryResponseRowsInner
tag_invoke(boost::json::value_to_tag<TokenizedConvertHistoryResponseRowsInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj =
        common::detail::json::as_object(jv, "TokenizedConvertHistoryResponseRowsInner");
    TokenizedConvertHistoryResponseRowsInner out;
    common::detail::json::read(obj, "underlyingAsset", out.underlying_asset);
    common::detail::json::read(obj, "underlyingAssetAmount", out.underlying_asset_amount);
    common::detail::json::read(obj, "tokenizedAsset", out.tokenized_asset);
    common::detail::json::read(obj, "tokenizedAssetAmount", out.tokenized_asset_amount);
    common::detail::json::read(obj, "issuerRequestId", out.issuer_request_id);
    common::detail::json::read(obj, "convertType", out.convert_type);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "createdAt", out.created_at);
    common::detail::json::read(obj, "updatedAt", out.updated_at);
    common::detail::json::read(obj, "tokenizedAssetSettleWalletType",
                               out.tokenized_asset_settle_wallet_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TokenizedConvertHistoryResponseRowsInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "underlyingAsset", v.underlying_asset);
    common::detail::json::write(obj, "underlyingAssetAmount", v.underlying_asset_amount);
    common::detail::json::write(obj, "tokenizedAsset", v.tokenized_asset);
    common::detail::json::write(obj, "tokenizedAssetAmount", v.tokenized_asset_amount);
    common::detail::json::write(obj, "issuerRequestId", v.issuer_request_id);
    common::detail::json::write(obj, "convertType", v.convert_type);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "createdAt", v.created_at);
    common::detail::json::write(obj, "updatedAt", v.updated_at);
    common::detail::json::write(obj, "tokenizedAssetSettleWalletType",
                                v.tokenized_asset_settle_wallet_type);
}

} // namespace binance::stocks::rest_api
