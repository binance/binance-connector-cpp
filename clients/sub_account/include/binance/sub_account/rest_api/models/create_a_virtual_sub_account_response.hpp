//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <optional>
#include <string>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/sub_account/export.hpp>

namespace binance::sub_account::rest_api {

struct CreateAVirtualSubAccountResponse {
    std::optional<std::string> email;

    bool operator==(const CreateAVirtualSubAccountResponse& /*other*/) const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT CreateAVirtualSubAccountResponse
tag_invoke(boost::json::value_to_tag<CreateAVirtualSubAccountResponse> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const CreateAVirtualSubAccountResponse& v);

} // namespace binance::sub_account::rest_api
