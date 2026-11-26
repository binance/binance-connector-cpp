//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/alpha/rest_api/models/token_list_response_data_inner.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::alpha::rest_api {

TokenListResponseDataInner tag_invoke(boost::json::value_to_tag<TokenListResponseDataInner> /*tag*/,
                                      const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "TokenListResponseDataInner");
    TokenListResponseDataInner out;
    common::detail::json::read(obj, "tokenId", out.token_id);
    common::detail::json::read(obj, "chainId", out.chain_id);
    common::detail::json::read(obj, "chainIconUrl", out.chain_icon_url);
    common::detail::json::read(obj, "chainName", out.chain_name);
    common::detail::json::read(obj, "contractAddress", out.contract_address);
    common::detail::json::read(obj, "name", out.name);
    common::detail::json::read(obj, "symbol", out.symbol);
    common::detail::json::read(obj, "iconUrl", out.icon_url);
    common::detail::json::read(obj, "price", out.price);
    common::detail::json::read(obj, "percentChange24h", out.percent_change24h);
    common::detail::json::read(obj, "volume24h", out.volume24h);
    common::detail::json::read(obj, "marketCap", out.market_cap);
    common::detail::json::read(obj, "fdv", out.fdv);
    common::detail::json::read(obj, "liquidity", out.liquidity);
    common::detail::json::read(obj, "totalSupply", out.total_supply);
    common::detail::json::read(obj, "circulatingSupply", out.circulating_supply);
    common::detail::json::read(obj, "holders", out.holders);
    common::detail::json::read(obj, "decimals", out.decimals);
    common::detail::json::read(obj, "listingCex", out.listing_cex);
    common::detail::json::read(obj, "hotTag", out.hot_tag);
    common::detail::json::read(obj, "cexCoinName", out.cex_coin_name);
    common::detail::json::read(obj, "canTransfer", out.can_transfer);
    common::detail::json::read(obj, "denomination", out.denomination);
    common::detail::json::read(obj, "offline", out.offline);
    common::detail::json::read(obj, "tradeDecimal", out.trade_decimal);
    common::detail::json::read(obj, "alphaId", out.alpha_id);
    common::detail::json::read(obj, "offsell", out.offsell);
    common::detail::json::read(obj, "priceHigh24h", out.price_high24h);
    common::detail::json::read(obj, "priceLow24h", out.price_low24h);
    common::detail::json::read(obj, "count24h", out.count24h);
    common::detail::json::read(obj, "onlineTge", out.online_tge);
    common::detail::json::read(obj, "onlineAirdrop", out.online_airdrop);
    common::detail::json::read(obj, "score", out.score);
    common::detail::json::read(obj, "cexOffDisplay", out.cex_off_display);
    common::detail::json::read(obj, "stockState", out.stock_state);
    common::detail::json::read(obj, "listingTime", out.listing_time);
    common::detail::json::read(obj, "mulPoint", out.mul_point);
    common::detail::json::read(obj, "bnExclusiveState", out.bn_exclusive_state);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const TokenListResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "tokenId", v.token_id);
    common::detail::json::write(obj, "chainId", v.chain_id);
    common::detail::json::write(obj, "chainIconUrl", v.chain_icon_url);
    common::detail::json::write(obj, "chainName", v.chain_name);
    common::detail::json::write(obj, "contractAddress", v.contract_address);
    common::detail::json::write(obj, "name", v.name);
    common::detail::json::write(obj, "symbol", v.symbol);
    common::detail::json::write(obj, "iconUrl", v.icon_url);
    common::detail::json::write(obj, "price", v.price);
    common::detail::json::write(obj, "percentChange24h", v.percent_change24h);
    common::detail::json::write(obj, "volume24h", v.volume24h);
    common::detail::json::write(obj, "marketCap", v.market_cap);
    common::detail::json::write(obj, "fdv", v.fdv);
    common::detail::json::write(obj, "liquidity", v.liquidity);
    common::detail::json::write(obj, "totalSupply", v.total_supply);
    common::detail::json::write(obj, "circulatingSupply", v.circulating_supply);
    common::detail::json::write(obj, "holders", v.holders);
    common::detail::json::write(obj, "decimals", v.decimals);
    common::detail::json::write(obj, "listingCex", v.listing_cex);
    common::detail::json::write(obj, "hotTag", v.hot_tag);
    common::detail::json::write(obj, "cexCoinName", v.cex_coin_name);
    common::detail::json::write(obj, "canTransfer", v.can_transfer);
    common::detail::json::write(obj, "denomination", v.denomination);
    common::detail::json::write(obj, "offline", v.offline);
    common::detail::json::write(obj, "tradeDecimal", v.trade_decimal);
    common::detail::json::write(obj, "alphaId", v.alpha_id);
    common::detail::json::write(obj, "offsell", v.offsell);
    common::detail::json::write(obj, "priceHigh24h", v.price_high24h);
    common::detail::json::write(obj, "priceLow24h", v.price_low24h);
    common::detail::json::write(obj, "count24h", v.count24h);
    common::detail::json::write(obj, "onlineTge", v.online_tge);
    common::detail::json::write(obj, "onlineAirdrop", v.online_airdrop);
    common::detail::json::write(obj, "score", v.score);
    common::detail::json::write(obj, "cexOffDisplay", v.cex_off_display);
    common::detail::json::write(obj, "stockState", v.stock_state);
    common::detail::json::write(obj, "listingTime", v.listing_time);
    common::detail::json::write(obj, "mulPoint", v.mul_point);
    common::detail::json::write(obj, "bnExclusiveState", v.bn_exclusive_state);
}

} // namespace binance::alpha::rest_api
