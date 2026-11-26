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
#include <utility>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/common/rest.hpp>
#include <binance/stock_options/export.hpp>
#include <binance/stock_options/rest_api/models/create_renew_listen_key_response.hpp>

namespace binance::stock_options::rest_api {

struct CreateRenewListenKeyParams {
    /// The value cannot be greater than `60000`.
    std::optional<std::int64_t> recv_window = std::nullopt;
};

class BINANCE_STOCK_OPTIONS_EXPORT UserDataStreamsApi {
public:
    explicit UserDataStreamsApi(std::shared_ptr<common::RestClient> client);

    /// Create / Renew Listen Key (USER_STREAM)
    ///
    /// POST /sapi/v1/equity/option/listenKey.
    ///
    /// Create or renew the user data stream `listenKey`.
    ///
    /// - **Valid for 1 hour.** Calling again renews it (resets to 1 hour) and returns the **same**
    /// key; renewing every 30 minutes is recommended. After expiry, a new key is issued and you
    /// must resubscribe with it.
    /// - **Options and stocks share one key.** The key is issued per user, not per asset class.
    /// This endpoint and `/sapi/v1/equity/listenKey` return the same key; calling either is enough.
    /// - Use the key to subscribe to the Order Report V2 Stream.
    ///
    /// Weight: 1
    ///
    /// Security Type: USER_STREAM
    ///
    /// See
    /// https://developers.binance.com/en/docs/catalog/advanced-trading-stock-option-trading/api/rest-api/user-data-streams#create-renew-listen-key
    [[nodiscard]] common::RestApiResponse<CreateRenewListenKeyResponse>
    create_renew_listen_key(const CreateRenewListenKeyParams& params = {}) const;

    /// Asynchronous `create_renew_listen_key()`. Completes with
    /// `void(std::exception_ptr, common::RestApiResponse<CreateRenewListenKeyResponse>)`.
    template <class CompletionToken>
    auto async_create_renew_listen_key(const CreateRenewListenKeyParams& params,
                                       CompletionToken&& token) const {
        return common::async_send<CreateRenewListenKeyResponse>(
            client_, create_renew_listen_key_request(params), std::forward<CompletionToken>(token));
    }

private:
    [[nodiscard]] common::RestRequest
    create_renew_listen_key_request(const CreateRenewListenKeyParams& params) const;

    std::shared_ptr<common::RestClient> client_;
};

} // namespace binance::stock_options::rest_api
