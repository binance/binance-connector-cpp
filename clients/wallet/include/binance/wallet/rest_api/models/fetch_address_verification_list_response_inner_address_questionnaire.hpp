//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct FetchAddressVerificationListResponseInnerAddressQuestionnaire {
    std::optional<std::int64_t> send_to;
    std::optional<std::string> satoshi_token;
    std::optional<std::int64_t> is_address_owner;
    std::optional<std::int64_t> verify_method;

    bool operator==(const FetchAddressVerificationListResponseInnerAddressQuestionnaire& /*other*/)
        const = default;
};

BINANCE_WALLET_EXPORT FetchAddressVerificationListResponseInnerAddressQuestionnaire
tag_invoke(boost::json::value_to_tag<
               FetchAddressVerificationListResponseInnerAddressQuestionnaire> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const FetchAddressVerificationListResponseInnerAddressQuestionnaire& v);

} // namespace binance::wallet::rest_api
