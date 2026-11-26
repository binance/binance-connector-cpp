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

struct DepositHistoryV2ResponseInnerQuestionnaire {
    std::optional<std::string> vasp_name;
    std::optional<std::int64_t> deposit_originator;

    bool operator==(const DepositHistoryV2ResponseInnerQuestionnaire& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT DepositHistoryV2ResponseInnerQuestionnaire
tag_invoke(boost::json::value_to_tag<DepositHistoryV2ResponseInnerQuestionnaire> /*tag*/,
           const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const DepositHistoryV2ResponseInnerQuestionnaire& v);

} // namespace binance::wallet::rest_api
