//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <utility>

#include <binance/c2c/c2c.hpp>
#include <binance/common/constants.hpp>

namespace binance::c2c {

std::string_view product_name() noexcept {
    return "c2c";
}

rest_api::RestApi rest_api::RestApi::from_config(common::RestApiConfig config) {
    if (!config.base_path) {
        config.base_path = common::constants::kC2CRestApiProdUrl;
    }
    return rest_api::RestApi(std::move(config));
}

rest_api::RestApi rest_api::RestApi::production(common::RestApiConfig config) {
    config.base_path = common::constants::kC2CRestApiProdUrl;
    return from_config(std::move(config));
}

} // namespace binance::c2c
