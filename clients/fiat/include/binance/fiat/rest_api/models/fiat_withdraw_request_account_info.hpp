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

#include <binance/fiat/export.hpp>

namespace binance::fiat::rest_api {

/// withdraw account info
struct FiatWithdrawRequestAccountInfo {
    /// Your destination bank account number is required to receive the withdrawal. In Argentina,
    /// this will be your CBU/CVU; in Mexico, it will be your CLABE.
    std::optional<std::string> account_number;
    /// Bank agency code. If contains a hyphen (e.g. `123-4`), enter `123` only.
    std::optional<std::string> agency;
    /// Bank code used for PIX routing.
    std::optional<std::string> bank_code_for_pix;
    /// Account type, e.g. `current` (Checking Account), `saving` (Savings Account), etc.
    std::optional<std::string> account_type;

    bool operator==(const FiatWithdrawRequestAccountInfo& /*other*/) const = default;
};

BINANCE_FIAT_EXPORT FiatWithdrawRequestAccountInfo
tag_invoke(boost::json::value_to_tag<FiatWithdrawRequestAccountInfo> /*tag*/,
           const boost::json::value& jv);
BINANCE_FIAT_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                    const FiatWithdrawRequestAccountInfo& v);

} // namespace binance::fiat::rest_api
