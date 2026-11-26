//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/stocks/rest_api/models/tokenized_mint_response.hpp>

namespace binance::stocks::rest_api {

TokenizedMintResponse tag_invoke(boost::json::value_to_tag<TokenizedMintResponse> /*tag*/,
                                 const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TokenizedMintResponse");
    TokenizedMintResponse out;
    common::detail::json::read(obj, "issuerRequestId", out.issuer_request_id);
    common::detail::json::read(obj, "status", out.status);
    common::detail::json::read(obj, "tokenizedAssetSettleWalletType",
                               out.tokenized_asset_settle_wallet_type);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TokenizedMintResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "issuerRequestId", v.issuer_request_id);
    common::detail::json::write(obj, "status", v.status);
    common::detail::json::write(obj, "tokenizedAssetSettleWalletType",
                                v.tokenized_asset_settle_wallet_type);
}

} // namespace binance::stocks::rest_api
