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

struct GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner {
    std::optional<std::string> email;
    std::optional<std::string> total_asset_of_btc;
    std::optional<std::string> total_liability_of_btc;
    std::optional<std::string> total_net_asset_of_btc;

    bool
    operator==(const GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner& /*other*/)
        const = default;
};

BINANCE_SUB_ACCOUNT_EXPORT GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner
tag_invoke(boost::json::value_to_tag<
               GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_SUB_ACCOUNT_EXPORT void
tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
           const GetSummaryOfSubAccountsMarginAccountResponseSubAccountListInner& v);

} // namespace binance::sub_account::rest_api
