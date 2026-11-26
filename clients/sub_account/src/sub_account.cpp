//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/common/constants.hpp>
#include <binance/sub_account/sub_account.hpp>

namespace binance::sub_account {

std::string_view product_name() noexcept {
    return "sub-account";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kSubAccountRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kSubAccountRestApiProdUrl;
    return from_config(std::move(config));
}

} // namespace binance::sub_account
