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
#include <vector>

#include <boost/json/fwd.hpp>
#include <boost/json/value.hpp>

#include <binance/pay/export.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_funds_detail_inner.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_payer_info.hpp>
#include <binance/pay/rest_api/models/get_pay_trade_history_response_data_inner_receiver_info.hpp>

namespace binance::pay::rest_api {

struct GetPayTradeHistoryResponseDataInner {
    /// Order type. Enum: PAY, PAY_REFUND, C2C, CRYPTO_BOX, CRYPTO_BOX_RF, C2C_HOLDING,
    /// C2C_HOLDING_RF, PAYOUT, REMITTANCE.
    std::optional<std::string> order_type;
    /// Transaction ID.
    std::optional<std::string> transaction_id;
    /// Trade timestamp.
    std::optional<std::int64_t> transaction_time;
    /// Order amount (up to 8 decimal places). Positive means income; negative means expenditure.
    std::optional<std::string> amount;
    /// Order asset.
    std::optional<std::string> currency;
    /// Main wallet type: 1=funding wallet, 2=spot wallet, 3=fiat wallet, 4 or 6=card payment,
    /// 5=earn wallet.
    std::optional<std::int64_t> wallet_type;
    /// Array format of wallet types. Multiple values may appear for combined payments.
    std::optional<std::vector<std::int64_t>> wallet_types;
    /// Funds usage details.
    std::optional<std::vector<GetPayTradeHistoryResponseDataInnerFundsDetailInner>> funds_detail;
    std::optional<GetPayTradeHistoryResponseDataInnerPayerInfo> payer_info;
    std::optional<GetPayTradeHistoryResponseDataInnerReceiverInfo> receiver_info;

    bool operator==(const GetPayTradeHistoryResponseDataInner& /*other*/) const = default;
};

BINANCE_PAY_EXPORT GetPayTradeHistoryResponseDataInner
tag_invoke(boost::json::value_to_tag<GetPayTradeHistoryResponseDataInner> /*tag*/,
           const boost::json::value& jv);
BINANCE_PAY_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const GetPayTradeHistoryResponseDataInner& v);

} // namespace binance::pay::rest_api
