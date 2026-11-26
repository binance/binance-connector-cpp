//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/utils.hpp>
#include <binance/w3w_prediction/rest_api/rest_api.hpp>
#include <binance/w3w_prediction/w3w_prediction.hpp>

namespace binance::w3w_prediction::rest_api {

RestApi::RestApi(common::RestApiConfig configuration)
    : client_(std::make_shared<common::RestClient>(
          std::move(configuration),
          common::detail::ClientOptions{.user_agent =
                                            common::detail::build_user_agent(product_name())})),
      market_data_api_(client_), otc_api_(client_), position_api_(client_), redeem_api_(client_),
      trade_api_(client_), transfer_api_(client_), wallet_api_(client_) {}

const common::RestApiConfig& RestApi::configuration() const noexcept {
    return client_->configuration();
}

} // namespace binance::w3w_prediction::rest_api
