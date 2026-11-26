//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

namespace binance::common::constants {

inline constexpr const char* kAlgoRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kAlphaRestApiProdUrl = "https://www.binance.com";

inline constexpr const char* kAlphaWebsocketStreamsProdUrl = "wss://nbstream.binance.com/w3w/wsa";

inline constexpr const char* kC2CRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kCmsWebsocketStreamsProdUrl = "wss://api.binance.com/sapi/wss";

inline constexpr const char* kConvertRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kCopyTradingRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kCryptoLoanRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kDerivativesTradingCoinFuturesRestApiProdUrl =
    "https://dapi.binance.com";
inline constexpr const char* kDerivativesTradingCoinFuturesRestApiTestnetUrl =
    "https://testnet.binancefuture.com";
inline constexpr const char* kDerivativesTradingCoinFuturesRestApiDemoUrl =
    "https://demo-dapi.binance.com";

inline constexpr const char* kDerivativesTradingCoinFuturesWebsocketApiProdUrl =
    "wss://ws-dapi.binance.com/ws-dapi/v1";
inline constexpr const char* kDerivativesTradingCoinFuturesWebsocketApiTestnetUrl =
    "wss://testnet.binancefuture.com/ws-dapi/v1";

inline constexpr const char* kDerivativesTradingCoinFuturesWebsocketStreamsProdUrl =
    "wss://dstream.binance.com";
inline constexpr const char* kDerivativesTradingCoinFuturesWebsocketStreamsTestnetUrl =
    "wss://dstream.binancefuture.com";
inline constexpr const char* kDerivativesTradingCoinFuturesWebsocketStreamsDemoUrl =
    "wss://demo-dstream.binance.com";

inline constexpr const char* kDerivativesTradingUsdsFuturesRestApiProdUrl =
    "https://fapi.binance.com";
inline constexpr const char* kDerivativesTradingUsdsFuturesRestApiTestnetUrl =
    "https://testnet.binancefuture.com";
inline constexpr const char* kDerivativesTradingUsdsFuturesRestApiDemoUrl =
    "https://demo-fapi.binance.com";

inline constexpr const char* kDerivativesTradingUsdsFuturesWebsocketApiProdUrl =
    "wss://ws-fapi.binance.com/ws-fapi/v1";
inline constexpr const char* kDerivativesTradingUsdsFuturesWebsocketApiTestnetUrl =
    "wss://testnet.binancefuture.com/ws-fapi/v1";

inline constexpr const char* kDerivativesTradingUsdsFuturesWebsocketStreamsProdUrl =
    "wss://fstream.binance.com";
inline constexpr const char* kDerivativesTradingUsdsFuturesWebsocketStreamsTestnetUrl =
    "wss://fstream.binancefuture.com";
inline constexpr const char* kDerivativesTradingUsdsFuturesWebsocketStreamsDemoUrl =
    "wss://demo-fstream.binance.com";

inline constexpr const char* kDerivativesTradingOptionsRestApiProdUrl = "https://eapi.binance.com";
inline constexpr const char* kDerivativesTradingOptionsRestApiTestnetUrl =
    "https://testnet.binancefuture.com";

inline constexpr const char* kDerivativesTradingOptionsWebsocketStreamsProdUrl =
    "wss://fstream.binance.com";
inline constexpr const char* kDerivativesTradingOptionsWebsocketStreamsTestnetUrl =
    "wss://fstream.binancefuture.com";

inline constexpr const char* kDerivativesTradingPortfolioMarginRestApiProdUrl =
    "https://papi.binance.com";
inline constexpr const char* kDerivativesTradingPortfolioMarginRestApiTestnetUrl =
    "https://testnet.binancefuture.com";

inline constexpr const char* kDerivativesTradingPortfolioMarginWebsocketStreamsProdUrl =
    "wss://fstream.binance.com/pm";
inline constexpr const char* kDerivativesTradingPortfolioMarginWebsocketStreamsTestnetUrl =
    "wss://fstream.binancefuture.com/pm";

inline constexpr const char* kDerivativesTradingPortfolioMarginProRestApiProdUrl =
    "https://api.binance.com";

inline constexpr const char* kDerivativesTradingPortfolioMarginProWebsocketStreamsProdUrl =
    "wss://fstream.binance.com/pm-classic";

inline constexpr const char* kDualInvestmentRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kFiatRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kGiftCardRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kMarginTradingRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kMarginTradingWebsocketStreamsProdUrl =
    "wss://stream.binance.com:9443";

inline constexpr const char* kMarginTradingRiskWebsocketStreamsProdUrl =
    "wss://margin-stream.binance.com";

inline constexpr const char* kMiningRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kPayRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kRebateRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kSimpleEarnRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kSpotRestApiProdUrl = "https://api.binance.com";
inline constexpr const char* kSpotRestApiTestnetUrl = "https://testnet.binance.vision";
inline constexpr const char* kSpotRestApiDemoUrl = "https://demo-api.binance.com";

inline constexpr const char* kSpotWebsocketApiProdUrl = "wss://ws-api.binance.com:443/ws-api/v3";
inline constexpr const char* kSpotWebsocketApiTestnetUrl =
    "wss://ws-api.testnet.binance.vision/ws-api/v3";
inline constexpr const char* kSpotWebsocketApiDemoUrl = "wss://demo-ws-api.binance.com/ws-api/v3";

inline constexpr const char* kSpotWebsocketStreamsProdUrl = "wss://stream.binance.com:9443";
inline constexpr const char* kSpotWebsocketStreamsTestnetUrl =
    "wss://stream.testnet.binance.vision";
inline constexpr const char* kSpotWebsocketStreamsDemoUrl = "wss://demo-stream.binance.com:9443";

inline constexpr const char* kSpotRestApiMarketUrl = "https://data-api.binance.vision";

inline constexpr const char* kSpotWebsocketStreamsMarketUrl = "wss://data-stream.binance.vision";

inline constexpr const char* kStakingRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kStockOptionsRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kStockOptionsWebsocketStreamsProdUrl =
    "wss://nbstream.binance.com/equity";

inline constexpr const char* kStocksRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kStocksWebsocketStreamsProdUrl = "wss://nbstream.binance.com/equity";

inline constexpr const char* kSubAccountRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kVipLoanRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kW3WPredictionRestApiProdUrl = "https://api.binance.com";

inline constexpr const char* kW3WPredictionWebsocketStreamsProdUrl =
    "wss://api.binance.com/sapi/wss";

inline constexpr const char* kWalletRestApiProdUrl = "https://api.binance.com";

} // namespace binance::common::constants
