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

#include <binance/simple_earn/export.hpp>
#include <binance/simple_earn/rest_api/models/get_collateral_record_response_rows_inner.hpp>

namespace binance::simple_earn::rest_api {

struct GetCollateralRecordResponse {
    std::optional<std::vector<GetCollateralRecordResponseRowsInner>> rows;
    std::optional<std::string> total;

    bool operator==(const GetCollateralRecordResponse& /*other*/) const = default;
};

BINANCE_SIMPLE_EARN_EXPORT GetCollateralRecordResponse tag_invoke(
    boost::json::value_to_tag<GetCollateralRecordResponse> /*tag*/, const boost::json::value& jv);
BINANCE_SIMPLE_EARN_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/,
                                           boost::json::value& jv,
                                           const GetCollateralRecordResponse& v);

} // namespace binance::simple_earn::rest_api
