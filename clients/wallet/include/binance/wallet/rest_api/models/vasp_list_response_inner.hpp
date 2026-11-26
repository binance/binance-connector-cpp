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

#include <binance/wallet/export.hpp>

namespace binance::wallet::rest_api {

struct VaspListResponseInner {
    std::optional<std::string> vasp_name;
    std::optional<std::string> vasp_code;
    /// For populating the `vasp` field in the deposit/withdrawal questionnaire
    std::optional<std::string> identifier;

    bool operator==(const VaspListResponseInner& /*other*/) const = default;
};

BINANCE_WALLET_EXPORT VaspListResponseInner
tag_invoke(boost::json::value_to_tag<VaspListResponseInner> /*tag*/, const boost::json::value& jv);
BINANCE_WALLET_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                      const VaspListResponseInner& v);

} // namespace binance::wallet::rest_api
