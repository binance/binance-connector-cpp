//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/fiat/fiat.hpp>
#include <binance/fiat/rest_api/rest_api.hpp>

namespace binance::fiat::rest_api {

RestApi::RestApi(common::RestApiConfig configuration)
    : client_(std::make_shared<common::RestClient>(
          std::move(configuration),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      api_(client_) {}

const common::RestApiConfig& RestApi::configuration() const noexcept {
    return client_->configuration();
}

} // namespace binance::fiat::rest_api
