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

#include <binance/cms/export.hpp>

namespace binance::cms::websocket_streams {

struct ComAnnouncementEnResponse {
    /// Catalog ID
    std::optional<std::int64_t> catalog_id;
    /// Catalog Name
    std::optional<std::string> catalog_name;
    /// Publish timestamp (milliseconds)
    std::optional<std::int64_t> publish_date;
    /// Announcement title
    std::optional<std::string> title;
    /// Announcement body
    std::optional<std::string> body;
    /// Disclaimer
    std::optional<std::string> disclaimer;

    bool operator==(const ComAnnouncementEnResponse& /*other*/) const = default;
};

BINANCE_CMS_EXPORT ComAnnouncementEnResponse tag_invoke(
    boost::json::value_to_tag<ComAnnouncementEnResponse> /*tag*/, const boost::json::value& jv);
BINANCE_CMS_EXPORT void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                                   const ComAnnouncementEnResponse& v);

} // namespace binance::cms::websocket_streams
