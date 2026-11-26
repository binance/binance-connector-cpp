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

#include <binance/common/required.hpp>
#include <binance/common/rest.hpp>
#include <binance/dual_investment/export.hpp>
#include <binance/dual_investment/rest_api/models/get_dual_investment_product_list_response.hpp>

namespace binance::dual_investment::rest_api {

enum class GetDualInvestmentProductListOptionTypeEnum {
    Call,
    Put,
    /// A value this SDK version does not know, which a newer value decodes to. It cannot be sent.
    Unknown,
};

[[nodiscard]] BINANCE_DUAL_INVESTMENT_EXPORT std::string_view
to_string(GetDualInvestmentProductListOptionTypeEnum value) noexcept;
BINANCE_DUAL_INVESTMENT_EXPORT GetDualInvestmentProductListOptionTypeEnum
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListOptionTypeEnum> /*tag*/,
           const boost::json::value& jv);
BINANCE_DUAL_INVESTMENT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                               boost::json::value& jv,
                                               GetDualInvestmentProductListOptionTypeEnum value);

struct GetDualInvestmentProductListParams {
    /// Input CALL or PUT
    common::Required<GetDualInvestmentProductListOptionTypeEnum> option_type;
    /// Target exercised asset, e.g.: if you subscribe to a high sell product (call option), you
    /// should input: `optionType: CALL`, `exercisedCoin: USDT`, `investCoin: BNB`; if you subscribe
    /// to a low buy product (put option), you should input: `optionType: PUT`, `exercisedCoin:
    /// BNB`, `investCoin: USDT`
    common::Required<std::string> exercised_coin;
    /// Asset used for subscribing, e.g.: if you subscribe to a high sell product (call option), you
    /// should input: `optionType: CALL`, `exercisedCoin: USDT`, `investCoin: BNB`; if you subscribe
    /// to a low buy product (put option), you should input: `optionType: PUT`, `exercisedCoin:
    /// BNB`, `investCoin: USDT`
    common::Required<std::string> invest_coin;
    /// Number of records per page
    std::optional<std::int64_t> page_size = std::nullopt;
    /// Page index
    std::optional<std::int64_t> page_index = std::nullopt;
    /// Request validity window in milliseconds
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_DUAL_INVESTMENT_EXPORT MarketDataApi {
public:
    explicit MarketDataApi(std::shared_ptr<common::RestClient> client);

    /// Get Dual Investment product list
    ///
    /// GET /sapi/v1/dci/product/list.
    ///
    /// Get Dual Investment product list
    ///
    /// Weight(IP): 1
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/investment-and-services-dual-investment/api/rest-api/market-data#get-dual-investment-product-list
    [[nodiscard]] common::RestApiResponse<GetDualInvestmentProductListResponse>
    get_dual_investment_product_list(const GetDualInvestmentProductListParams& params) const;

    /// Asynchronous `get_dual_investment_product_list()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<GetDualInvestmentProductListResponse>)`.
    template <class CompletionToken>
    auto async_get_dual_investment_product_list(const GetDualInvestmentProductListParams& params,
                                                CompletionToken&& token) const {
        return common::async_send<GetDualInvestmentProductListResponse>(
            client_, get_dual_investment_product_list_request(params),
            std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest get_dual_investment_product_list_request(
        const GetDualInvestmentProductListParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::dual_investment::rest_api
