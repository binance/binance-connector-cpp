//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/wallet/rest_api/rest_api.hpp>
#include <binance/wallet/wallet.hpp>

namespace binance::wallet::rest_api {

RestApi::RestApi(common::RestApiConfig configuration)
    : client_(std::make_shared<common::RestClient>(
          std::move(configuration),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      account_api_(client_), asset_api_(client_), capital_api_(client_), others_api_(client_),
      travel_rule_api_(client_) {}

const common::RestApiConfig& RestApi::configuration() const noexcept {
    return client_->configuration();
}

} // namespace binance::wallet::rest_api
