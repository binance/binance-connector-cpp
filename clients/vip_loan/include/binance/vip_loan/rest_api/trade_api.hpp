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

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/decimal.hpp>
#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/vip_loan/export.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_borrow_response.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_fixed_rate_borrow_response.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_renew_response.hpp>
#include <binance/vip_loan/rest_api/models/vip_loan_repay_response.hpp>

namespace binance::vip_loan::rest_api {

struct VipLoanBorrowParams {
    common::Required<std::int64_t> loan_account_id;
    common::Required<std::string> loan_coin;
    common::Required<common::Decimal> loan_amount;
    /// Collateral account ID(s). Multiple split by `,`
    common::Required<std::string> collateral_account_id;
    /// Collateral coin(s), multiple separated by `,`. Use `<ASSET>-Earn` for a Simple Earn Flexible
    /// position; it must be sent together with its Spot asset, e.g. `USDT,USDT-Earn`.
    common::Required<std::string> collateral_coin;
    /// TRUE: flexible rate; FALSE: fixed rate
    common::Required<bool> is_flexible_rate;
    /// Mandatory for fixed rate. Optional for flexible rate. e.g. 30/60 days
    std::optional<std::int64_t> loan_term = std::nullopt;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct VipLoanFixedRateBorrowParams {
    /// Supply request string, positional encoding (no key). Multiple entries separated by `;`,
    /// fields separated by `:`, order: `<requestId>:<interestRate>:<amount>`. Example:
    /// `1212:0.12:100;3434:0.13:50`
    common::Required<std::string> supply_request;
    /// Borrow coin
    common::Required<std::string> borrow_coin;
    /// Loan term in days
    common::Required<std::int64_t> loan_term;
    /// Borrow receiving account UID
    common::Required<std::int64_t> borrow_uid;
    /// Collateral coin(s), multiple separated by `,`. Only coin names, no amount (VIP loan
    /// collateral amount = entire Spot balance of the coin; for `<ASSET>-Earn`, the Simple Earn
    /// Flexible position of the asset). `<ASSET>-Earn` must be sent together with its Spot asset,
    /// e.g. `BNB,BNB-Earn`.
    common::Required<std::string> collateral_coin;
    /// Collateral account ID(s), multiple separated by `,`
    common::Required<std::string> collateral_account_id;
    /// Default: `true`. `true`: auto repay at expiration; `false`: auto-convert to flexible
    /// (floating rate) at expiration
    std::optional<bool> auto_repay = std::nullopt;
    /// The value cannot be greater than `60000`
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct VipLoanRenewParams {
    common::Required<std::int64_t> order_id;
    /// 30/60 days
    common::Required<std::int64_t> loan_term;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

struct VipLoanRepayParams {
    common::Required<std::int64_t> order_id;
    common::Required<common::Decimal> amount;
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_VIP_LOAN_EXPORT TradeApi {
public:
    explicit TradeApi(std::shared_ptr<common::RestClient> client);

    /// VIP Loan Borrow (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/borrow.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - `loanAccountId` refers to the loan receiving account.
    /// - Only master account applications are supported.
    /// - `loanAccountId` and `collateralAccountId` must be under the same master account.
    /// - `loanTerm` is mandatory if the user chooses a fixed rate (`isFlexibleRate = FALSE`).
    /// - Every coin in `collateralCoin` is pledged from every account in `collateralAccountId`.
    /// - To pledge a Simple Earn Flexible position, add `<ASSET>-Earn` (e.g. `USDT-Earn`) to
    /// `collateralCoin` together with its Spot asset (e.g. `USDT,USDT-Earn`). Sending
    /// `<ASSET>-Earn` without its Spot asset returns `-10213`.
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-borrow
    [[nodiscard]] common::RestApiResponse<VipLoanBorrowResponse>
    vip_loan_borrow(const VipLoanBorrowParams& params) const;

    /// Asynchronous `vip_loan_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VipLoanBorrowResponse>)`.
    template <class CompletionToken>
    auto async_vip_loan_borrow(const VipLoanBorrowParams& params, CompletionToken&& token) const {
        return common::async_send<VipLoanBorrowResponse>(client_, vip_loan_borrow_request(params),
                                                         std::forward<CompletionToken>(token));
    }

    /// VIP Loan Fixed Rate Borrow (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/fixed/borrow.
    ///
    /// Submit a fixed rate borrow request by matching market supply orders.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - **Rate limit:** 2 requests per second per account.
    /// - When multiple `supplyRequest` entries are provided, all `requestId` values must correspond
    /// to the same `borrowCoin` and `loanTerm` (validated by collateral facade).
    /// - Every coin in `collateralCoin` is pledged from every account in `collateralAccountId`.
    /// - To pledge a Simple Earn Flexible position, add `<ASSET>-Earn` (e.g. `BNB-Earn`) to
    /// `collateralCoin` together with its Spot asset (e.g. `BNB,BNB-Earn`). Sending `<ASSET>-Earn`
    /// without its Spot asset returns `-10213`.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-fixed-rate-borrow
    [[nodiscard]] common::RestApiResponse<VipLoanFixedRateBorrowResponse>
    vip_loan_fixed_rate_borrow(const VipLoanFixedRateBorrowParams& params) const;

    /// Asynchronous `vip_loan_fixed_rate_borrow()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VipLoanFixedRateBorrowResponse>)`.
    template <class CompletionToken>
    auto async_vip_loan_fixed_rate_borrow(const VipLoanFixedRateBorrowParams& params,
                                          CompletionToken&& token) const {
        return common::async_send<VipLoanFixedRateBorrowResponse>(
            client_, vip_loan_fixed_rate_borrow_request(params),
            std::forward<CompletionToken>(token));
    }

    /// VIP Loan Renew (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/renew.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-renew
    [[nodiscard]] common::RestApiResponse<VipLoanRenewResponse>
    vip_loan_renew(const VipLoanRenewParams& params) const;

    /// Asynchronous `vip_loan_renew()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VipLoanRenewResponse>)`.
    template <class CompletionToken>
    auto async_vip_loan_renew(const VipLoanRenewParams& params, CompletionToken&& token) const {
        return common::async_send<VipLoanRenewResponse>(client_, vip_loan_renew_request(params),
                                                        std::forward<CompletionToken>(token));
    }

    /// VIP Loan Repay (TRADE)
    ///
    /// POST /sapi/v1/loan/vip/repay.
    ///
    /// VIP loan is available for VIP users only.
    ///
    /// Weight(UID): 6000
    ///
    /// Security Type: TRADE
    ///
    /// Notes:
    /// - Rate limit: 1 request per second per account.
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-vip-loan/api/rest-api/trade#vip-loan-repay
    [[nodiscard]] common::RestApiResponse<VipLoanRepayResponse>
    vip_loan_repay(const VipLoanRepayParams& params) const;

    /// Asynchronous `vip_loan_repay()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<VipLoanRepayResponse>)`.
    template <class CompletionToken>
    auto async_vip_loan_repay(const VipLoanRepayParams& params, CompletionToken&& token) const {
        return common::async_send<VipLoanRepayResponse>(client_, vip_loan_repay_request(params),
                                                        std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    vip_loan_borrow_request(const VipLoanBorrowParams& params) const;
    [[nodiscard]] common::RestRequest
    vip_loan_fixed_rate_borrow_request(const VipLoanFixedRateBorrowParams& params) const;
    [[nodiscard]] common::RestRequest
    vip_loan_renew_request(const VipLoanRenewParams& params) const;
    [[nodiscard]] common::RestRequest
    vip_loan_repay_request(const VipLoanRepayParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::vip_loan::rest_api
