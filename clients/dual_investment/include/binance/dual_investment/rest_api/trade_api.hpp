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
#include <string_view>
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/dual_investment/export.hpp>
#include <binance/dual_investment/rest_api/models/check_dual_investment_accounts_response.hpp>
#include <binance/dual_investment/rest_api/models/get_dual_investment_positions_response.hpp>
#include <binance/dual_investment/rest_api/models/subscribe_dual_investment_products_response.hpp>

namespace binance::dual_investment::rest_api {

enum class GetDualInvestmentPositionsStatusEnum {
    Pending,
    PurchaseSuccess,
    Settled,
    PurchaseFail,
    Refunding,
    RefundSuccess,
    Settling,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DUAL_INVESTMENT_EXPORT std::string_view
to_string(GetDualInvestmentPositionsStatusEnum value) noexcept;
BINANCE_DUAL_INVESTMENT_EXPORT GetDualInvestmentPositionsStatusEnum
tag_invoke(boost::json::value_to_tag<GetDualInvestmentPositionsStatusEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                               boost::json::value& jv,
                                               GetDualInvestmentPositionsStatusEnum value);

struct CheckDualInvestmentAccountsParams {
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct GetDualInvestmentPositionsParams {
    /// `PENDING`: Products are purchasing, will give results later; `PURCHASE_SUCCESS`: purchase
    /// successfully; `SETTLED`: Products are finish settling; `PURCHASE_FAIL`: fail to purchase;
    /// `REFUNDING`: refund ongoing; `REFUND_SUCCESS`: refund to spot account successfully;
    /// `SETTLING`: Products are settling. If don't fill this field, will response all the position
    /// status.
    std::optional<GetDualInvestmentPositionsStatusEnum> status = std::nullopt;
    /// Number of records per page
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Page index
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct SubscribeDualInvestmentProductsParams {
    /// get id from `/sapi/v1/dci/product/list`
    common::Required<std::string> id;
    /// get orderId from `/sapi/v1/dci/product/list`
    common::Required<std::string> order_id;
    /// the amount for subscribing
    common::Required<common::Decimal> deposit_amount;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DUAL_INVESTMENT_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// Check Dual Investment accounts (USER_DATA)
    ///
    /// GET /sapi/v1/dci/product/accounts.
    ///
    /// Check Dual Investment accounts
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#check-dual-investment-accounts
    [[nodiscard]] common::RestApiResponse<CheckDualInvestmentAccountsResponse>
    check_dual_investment_accounts(const CheckDualInvestmentAccountsParams& params = {}) const;

    /// Asynchronous `check_dual_investment_accounts()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CheckDualInvestmentAccountsResponse>)`.
    template <class CompletionToken>
    auto async_check_dual_investment_accounts(const CheckDualInvestmentAccountsParams& params,
                                              CompletionToken&& token) const {
        return common::async_send<CheckDualInvestmentAccountsResponse>(
            client_, check_dual_investment_accounts_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Get Dual Investment positions (USER_DATA)
    ///
    /// GET /sapi/v1/dci/product/positions.
    ///
    /// Get Dual Investment positions (batch)
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#get-dual-investment-positions
    [[nodiscard]] common::RestApiResponse<GetDualInvestmentPositionsResponse>
    get_dual_investment_positions(const GetDualInvestmentPositionsParams& params = {}) const;

    /// Asynchronous `get_dual_investment_positions()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetDualInvestmentPositionsResponse>)`.
    template <class CompletionToken>
    auto async_get_dual_investment_positions(const GetDualInvestmentPositionsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<GetDualInvestmentPositionsResponse>(
            client_, get_dual_investment_positions_request(params),
            std::forward<CompletionToken>(token));
    }

    /// Subscribe Dual Investment products (USER_DATA)
    ///
    /// POST /sapi/v1/dci/product/subscribe.
    ///
    /// Subscribe Dual Investment products
    ///
    /// Weight(IP): 1
    ///
    /// Security Type: USER_DATA
    ///
    /// Notes:
    /// - Failed messages:
    ///   - Products are not available. This means APR changed to a lower value, or the order is
    ///   unavailable.
    ///   - Failed. This means system or network errors.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/trade#subscribe-dual-investment-products
    [[nodiscard]] common::RestApiResponse<SubscribeDualInvestmentProductsResponse>
    subscribe_dual_investment_products(const SubscribeDualInvestmentProductsParams& params) const;

    /// Asynchronous `subscribe_dual_investment_products()`. Completes with
    /// `void(std::exception_ptr,
    /// common::RestApiResponse<SubscribeDualInvestmentProductsResponse>)`.
    template <class CompletionToken>
    auto
    async_subscribe_dual_investment_products(const SubscribeDualInvestmentProductsParams& params,
                                             CompletionToken&& token) const {
        return common::async_send<SubscribeDualInvestmentProductsResponse>(
            client_, subscribe_dual_investment_products_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    check_dual_investment_accounts_request(const CheckDualInvestmentAccountsParams& params) const;
    [[nodiscard]] common::RestRequest
    get_dual_investment_positions_request(const GetDualInvestmentPositionsParams& params) const;
    [[nodiscard]] common::RestRequest subscribe_dual_investment_products_request(
        const SubscribeDualInvestmentProductsParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::dual_investment::rest_api
