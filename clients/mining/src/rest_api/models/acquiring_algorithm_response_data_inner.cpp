//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/common/detail/json.hpp>
#include <binance/mining/rest_api/models/acquiring_algorithm_response_data_inner.hpp>

namespace binance::mining::rest_api {

AcquiringAlgorithmResponseDataInner
tag_invoke(boost::json::value_to_tag<AcquiringAlgorithmResponseDataInner> /*tag*/,
           const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "AcquiringAlgorithmResponseDataInner");
    AcquiringAlgorithmResponseDataInner out;
    common::detail::json::read(obj, "algoName", out.algo_name);
    common::detail::json::read(obj, "algoId", out.algo_id);
    common::detail::json::read(obj, "poolIndex", out.pool_index);
    common::detail::json::read(obj, "unit", out.unit);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const AcquiringAlgorithmResponseDataInner& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "algoName", v.algo_name);
    common::detail::json::write(obj, "algoId", v.algo_id);
    common::detail::json::write(obj, "poolIndex", v.pool_index);
    common::detail::json::write(obj, "unit", v.unit);
}

} // namespace binance::mining::rest_api
