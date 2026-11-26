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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/alpha/export.hpp>

namespace binance::alpha::rest_api {

struct TokenListResponseDataInner {
    /// Unique token identifier.
    std::optional<std::string> token_id;
    /// Chain ID.
    std::optional<std::string> chain_id;
    /// Chain icon URL.
    std::optional<std::string> chain_icon_url;
    /// Chain name.
    std::optional<std::string> chain_name;
    /// Token contract address.
    std::optional<std::string> contract_address;
    /// Token name.
    std::optional<std::string> name;
    /// Token symbol.
    std::optional<std::string> symbol;
    /// Token icon URL.
    std::optional<std::string> icon_url;
    /// Latest token price.
    std::optional<std::string> price;
    /// 24-hour price change percentage.
    std::optional<std::string> percent_change24h;
    /// 24-hour trading volume.
    std::optional<std::string> volume24h;
    std::optional<std::string> market_cap;
    std::optional<std::string> fdv;
    std::optional<std::string> liquidity;
    std::optional<std::string> total_supply;
    std::optional<std::string> circulating_supply;
    std::optional<std::string> holders;
    std::optional<std::int64_t> decimals;
    std::optional<bool> listing_cex;
    std::optional<bool> hot_tag;
    std::optional<std::string> cex_coin_name;
    std::optional<bool> can_transfer;
    std::optional<std::int64_t> denomination;
    std::optional<bool> offline;
    std::optional<std::int64_t> trade_decimal;
    /// ALPHA token ID, e.g. ALPHA_175.
    std::optional<std::string> alpha_id;
    std::optional<bool> offsell;
    std::optional<std::string> price_high24h;
    std::optional<std::string> price_low24h;
    std::optional<std::string> count24h;
    std::optional<bool> online_tge;
    std::optional<bool> online_airdrop;
    std::optional<std::int64_t> score;
    std::optional<bool> cex_off_display;
    std::optional<bool> stock_state;
    std::optional<std::int64_t> listing_time;
    std::optional<std::int64_t> mul_point;
    std::optional<bool> bn_exclusive_state;

    bool operator==(const TokenListResponseDataInner& /*other*/) const = default;
};

BINANCE_ALPHA_EXPORT TokenListResponseDataInner tag_invoke(
    boost::json::value_to_tag<TokenListResponseDataInner> /*tag*/, const boost::json::value& jv);
BINANCE_ALPHA_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                     const TokenListResponseDataInner& v);

} // namespace binance::alpha::rest_api
