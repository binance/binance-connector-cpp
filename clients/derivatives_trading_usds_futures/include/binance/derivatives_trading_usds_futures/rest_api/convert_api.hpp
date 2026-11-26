//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/derivatives_trading_usds_futures/export.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/accept_the_offered_quote_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/list_all_convert_pairs_response_inner.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/order_status_response.hpp>
#include <binance/derivatives_trading_usds_futures/rest_api/models/send_quote_request_response.hpp>

namespace binance::derivatives_trading_usds_futures::rest_api {

struct AcceptTheOfferedQuoteParams {
    common::Required<std::string> quote_id;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct ListAllConvertPairsParams {
    /// User spends coin
    std::optional<std::string> from_asset = std::nullopt;
    /// User receives coin
    std::optional<std::string> to_asset = std::nullopt;
};

struct OrderStatusParams {
    /// Either orderId or quoteId is required
    std::optional<std::string> order_id = std::nullopt;
    /// Either orderId or quoteId is required
    std::optional<std::string> quote_id = std::nullopt;
};

struct SendQuoteRequestParams {
    common::Required<std::string> from_asset;
    common::Required<std::string> to_asset;
    /// When specified, it is the amount you will be debited after the conversion
    std::optional<common::Decimal> from_amount = std::nullopt;
    /// When specified, it is the amount you will be credited after the conversion
    std::optional<common::Decimal> to_amount = std::nullopt;
    /// 10s, default 10s
    std::optional<std::string> valid_time = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DERIVATIVES_TRADING_USDS_FUTURES_EXPORT ConvertApi {
public:
    explicit ConvertApi(std::shared_ptr<common::RestClient> client);

    /// Accept the offered quote (USER_DATA)
    ///
    /// POST /fapi/v1/convert/acceptQuote.
    ///
    /// Accept the offered quote by quote ID.
    ///
    /// Weight(IP): 200
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/convert#accept-the-offered-quote
    [[nodiscard]] common::RestApiResponse<AcceptTheOfferedQuoteResponse>
    accept_the_offered_quote(const AcceptTheOfferedQuoteParams& params) const;

    /// Asynchronous `accept_the_offered_quote()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<AcceptTheOfferedQuoteResponse>)`.
    template <class CompletionToken>
    auto async_accept_the_offered_quote(const AcceptTheOfferedQuoteParams& params,
                                        CompletionToken&& token) const {
        return common::async_send<AcceptTheOfferedQuoteResponse>(
            client_, accept_the_offered_quote_request(params),
            std::forward<CompletionToken>(token));
    }

    /// List All Convert Pairs
    ///
    /// GET /fapi/v1/convert/exchangeInfo.
    ///
    /// Query for all convertible token pairs and the tokens’ respective upper/lower limits
    ///
    /// Weight(IP): 20
    ///
    /// Notes:
    /// - User needs to supply either or both of the input parameter
    /// - If not defined for both fromAsset and toAsset, only partial token pairs will be returned
    /// - Asset BNFCR is only available to convert for MICA region users.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/convert#list-all-convert-pairs
    [[nodiscard]] common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>
    list_all_convert_pairs(const ListAllConvertPairsParams& params = {}) const;

    /// Asynchronous `list_all_convert_pairs()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<std::vector<ListAllConvertPairsResponseInner>>)`.
    template <class CompletionToken>
    auto async_list_all_convert_pairs(const ListAllConvertPairsParams& params,
                                      CompletionToken&& token) const {
        return common::async_send<std::vector<ListAllConvertPairsResponseInner>>(
            client_, list_all_convert_pairs_request(params), std::forward<CompletionToken>(token));
    }

    /// Order status (USER_DATA)
    ///
    /// GET /fapi/v1/convert/orderStatus.
    ///
    /// Query order status by order ID.
    ///
    /// Weight(IP): 50
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/convert#order-status
    [[nodiscard]] common::RestApiResponse<OrderStatusResponse>
    order_status(const OrderStatusParams& params = {}) const;

    /// Asynchronous `order_status()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<OrderStatusResponse>)`.
    template <class CompletionToken>
    auto async_order_status(const OrderStatusParams& params, CompletionToken&& token) const {
        return common::async_send<OrderStatusResponse>(client_, order_status_request(params),
                                                       std::forward<CompletionToken>(token));
    }

    /// Send Quote Request (USER_DATA)
    ///
    /// POST /fapi/v1/convert/getQuote.
    ///
    /// Request a quote for the requested token pairs
    ///
    /// Weight: 50(IP)
    /// 360/hour, 500/day
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Either fromAmount or toAmount should be sent
    /// - `quoteId` will be returned only if you have enough funds to convert
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/core-trading-derivatives-trading-usd-s-m-futures/api/rest-api/convert#send-quote-request
    [[nodiscard]] common::RestApiResponse<SendQuoteRequestResponse>
    send_quote_request(const SendQuoteRequestParams& params) const;

    /// Asynchronous `send_quote_request()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<SendQuoteRequestResponse>)`.
    template <class CompletionToken>
    auto async_send_quote_request(const SendQuoteRequestParams& params,
                                  CompletionToken&& token) const {
        return common::async_send<SendQuoteRequestResponse>(
            client_, send_quote_request_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    accept_the_offered_quote_request(const AcceptTheOfferedQuoteParams& params) const;
    [[nodiscard]] common::RestRequest
    list_all_convert_pairs_request(const ListAllConvertPairsParams& params) const;
    [[nodiscard]] common::RestRequest order_status_request(const OrderStatusParams& params) const;
    [[nodiscard]] common::RestRequest
    send_quote_request_request(const SendQuoteRequestParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::derivatives_trading_usds_futures::rest_api
