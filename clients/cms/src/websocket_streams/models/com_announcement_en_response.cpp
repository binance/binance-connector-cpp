//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <binance/cms/websocket_streams/models/com_announcement_en_response.hpp>
#include <binance/common/detail/json.hpp>

namespace binance::cms::websocket_streams {

ComAnnouncementEnResponse tag_invoke(boost::json::value_to_tag<ComAnnouncementEnResponse> /*tag*/,
                                     const boost::json::value& jv) {
    const auto& obj = common::detail::json::as_object(jv, "ComAnnouncementEnResponse");
    ComAnnouncementEnResponse out;
    common::detail::json::read(obj, "catalogId", out.catalog_id);
    common::detail::json::read(obj, "catalogName", out.catalog_name);
    common::detail::json::read(obj, "publishDate", out.publish_date);
    common::detail::json::read(obj, "title", out.title);
    common::detail::json::read(obj, "body", out.body);
    common::detail::json::read(obj, "disclaimer", out.disclaimer);
    return out;
}

void tag_invoke(boost::json::value_from_tag /*tag*/, boost::json::value& jv,
                const ComAnnouncementEnResponse& v) {
    auto& obj = jv.emplace_object();
    common::detail::json::write(obj, "catalogId", v.catalog_id);
    common::detail::json::write(obj, "catalogName", v.catalog_name);
    common::detail::json::write(obj, "publishDate", v.publish_date);
    common::detail::json::write(obj, "title", v.title);
    common::detail::json::write(obj, "body", v.body);
    common::detail::json::write(obj, "disclaimer", v.disclaimer);
}

} // namespace binance::cms::websocket_streams
