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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/mining/export.hpp>
#include <binance/mining/rest_api/models/account_list_response_data_inner_list_inner.hpp>

namespace binance::mining::rest_api {

struct AccountListResponseDataInner {
    /// Type of hashrate bucket
    std::optional<std::string> type;
    /// Mining account
    std::optional<std::string> user_name;
    std::optional<std::vector<AccountListResponseDataInnerListInner>> list;

    bool operator==(const AccountListResponseDataInner& /*other*/) const = default;
};

BINANCE_MINING_EXPORT AccountListResponseDataInner tag_invoke(
    boost::json::value_to_tag<AccountListResponseDataInner> /*tag*/, const boost::json::value& jv);
BINANCE_MINING_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const AccountListResponseDataInner& v);

} // namespace binance::mining::rest_api
