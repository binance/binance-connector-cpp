//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <stdexcept>

#include <binance/common/detail/json.hpp>
#include <binance/dual_investment/rest_api/market_data_api.hpp>

namespace binance::dual_investment::rest_api {

namespace {
constexpr bool kHasTimeUnit = false;
} // namespace

std::string_view to_string(GetDualInvestmentProductListOptionTypeEnum value) noexcept {
    switch (value) {
    case GetDualInvestmentProductListOptionTypeEnum::Call:
        return "CALL";
    case GetDualInvestmentProductListOptionTypeEnum::Put:
        return "PUT";
    case GetDualInvestmentProductListOptionTypeEnum::Unknown:
        break;
    }
    return "";
}

GetDualInvestmentProductListOptionTypeEnum
tag_invoke(boost::json::value_to_tag<GetDualInvestmentProductListOptionTypeEnum> /*tag*/,
           const boost::json::value& jv) {
    const std::string_view s = jv.as_string();
    if (s == "CALL") {
        return GetDualInvestmentProductListOptionTypeEnum::Call;
    }
    if (s == "PUT") {
        return GetDualInvestmentProductListOptionTypeEnum::Put;
    }
    return GetDualInvestmentProductListOptionTypeEnum::Unknown;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                GetDualInvestmentProductListOptionTypeEnum value) {
    if (value == GetDualInvestmentProductListOptionTypeEnum::Unknown) {
        throw std::invalid_argument(
            "GetDualInvestmentProductListOptionTypeEnum::Unknown cannot be sent");
    }
    jv = to_string(value);
}

MarketDataApi::MarketDataApi(std::shared_ptr<common::RestClient> client)
    : client_(std::move(client)) {}

common::RestRequest MarketDataApi::get_dual_investment_product_list_request(
    const GetDualInvestmentProductListParams& params) const {
    common::RestRequest req;
    req.method = common::HttpMethod::Get;
    req.endpoint = "/sapi/v1/dci/product/list";
    common::detail::json::set_param(req.query, "optionType", params.option_type);
    common::detail::json::set_param(req.query, "exercisedCoin", params.exercised_coin);
    common::detail::json::set_param(req.query, "investCoin", params.invest_coin);
    common::detail::json::set_param(req.query, "pageSize", params.page_size);
    common::detail::json::set_param(req.query, "pageIndex", params.page_index);
    common::detail::json::set_param(req.query, "recvWindow", params.recv_window);
    req.time_unit = kHasTimeUnit ? client_->configuration().time_unit : std::nullopt;
    req.is_signed = false;
    return req;
}

common::RestApiResponse<GetDualInvestmentProductListResponse>
MarketDataApi::get_dual_investment_product_list(
    const GetDualInvestmentProductListParams& params) const {
    return common::send<GetDualInvestmentProductListResponse>(
        *client_, get_dual_investment_product_list_request(params));
}

} // namespace binance::dual_investment::rest_api
