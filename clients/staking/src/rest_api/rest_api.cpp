//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/staking/rest_api/rest_api.hpp>
#include <binance/staking/staking.hpp>

namespace binance::staking::rest_api {

RestApi::RestApi(common::RestApiConfig configuration)
    : client_(std::make_shared<common::RestClient>(
          std::move(configuration),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      eth_staking_api_(client_), on_chain_yields_api_(client_), soft_staking_api_(client_),
      sol_staking_api_(client_) {}

const common::RestApiConfig& RestApi::configuration() const noexcept {
    return client_->configuration();
}

} // namespace binance::staking::rest_api
