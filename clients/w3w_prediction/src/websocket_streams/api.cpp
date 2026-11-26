//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <algorithm>
#include <cctype>
#include <charconv>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

#include <binance/common/detail/json.hpp>
#include <binance/common/detail/utils.hpp>
#include <binance/w3w_prediction/websocket_streams/api.hpp>

namespace binance::w3w_prediction::websocket_streams {

namespace {

// An all-digit id that fits 32 bits is sent as a number, anything else as a string.
common::StreamId to_stream_id(const std::string& id) {
    if (!id.empty() &&
        std::all_of(id.begin(), id.end(), [](unsigned char c) { return std::isdigit(c) != 0; })) {
        std::uint32_t number = 0;
        const auto [end, ec] = std::from_chars(id.data(), id.data() + id.size(), number);
        if (ec == std::errc() && end == id.data() + id.size()) {
            return number;
        }
    }
    return id;
}

// Fills the placeholders of `path` (`<symbol>@aggTrade`) from `params` and subscribes.
template <class T>
common::WebsocketStream<T> create_stream(common::WebsocketStreams& client, std::string_view path,
                                         const common::Params& params,
                                         std::optional<std::string> url_path) {
    std::map<std::string, std::string> variables;
    for (const auto& [key, value] : params) {
        variables.emplace(std::string(key), common::detail::param_to_string(value));
    }
    std::optional<common::StreamId> id;
    if (const auto it = variables.find("id"); it != variables.end()) {
        id = to_stream_id(it->second);
    }
    return common::WebsocketStream<T>(client.create_stream(
        common::detail::replace_websocket_streams_placeholders(path, variables), std::move(id),
        std::move(url_path)));
}

} // namespace

Api::Api(std::shared_ptr<common::WebsocketStreams> client) : client_(std::move(client)) {}

common::WebsocketStream<BatchClaimPartiallySucceededResponse>
Api::batch_claim_partially_succeeded() const {
    common::Params p;
    return create_stream<BatchClaimPartiallySucceededResponse>(
        *client_, "/web3_prediction_pm_claim_partial_success", p, std::nullopt);
}

common::WebsocketStream<FundTransferFailedResponse> Api::fund_transfer_failed() const {
    common::Params p;
    return create_stream<FundTransferFailedResponse>(*client_, "/web3_prediction_pm_transfer_fail",
                                                     p, std::nullopt);
}

common::WebsocketStream<FundTransferSucceededResponse> Api::fund_transfer_succeeded() const {
    common::Params p;
    return create_stream<FundTransferSucceededResponse>(
        *client_, "/web3_prediction_pm_transfer_success", p, std::nullopt);
}

common::WebsocketStream<LimitOrderFullyFilledResponse> Api::limit_order_fully_filled() const {
    common::Params p;
    return create_stream<LimitOrderFullyFilledResponse>(
        *client_, "/web3_prediction_pm_limit_order_filled", p, std::nullopt);
}

common::WebsocketStream<LimitOrderPartiallyFilledResponse>
Api::limit_order_partially_filled() const {
    common::Params p;
    return create_stream<LimitOrderPartiallyFilledResponse>(
        *client_, "/web3_prediction_pm_limit_order_partial_fill", p, std::nullopt);
}

common::WebsocketStream<LimitOrderSubmissionFailedResponse>
Api::limit_order_submission_failed() const {
    common::Params p;
    return create_stream<LimitOrderSubmissionFailedResponse>(
        *client_, "/web3_prediction_pm_limit_submit_fail", p, std::nullopt);
}

common::WebsocketStream<LimitOrderSubmittedSuccessfullyResponse>
Api::limit_order_submitted_successfully() const {
    common::Params p;
    return create_stream<LimitOrderSubmittedSuccessfullyResponse>(
        *client_, "/web3_prediction_pm_limit_submit_success", p, std::nullopt);
}

common::WebsocketStream<MarketBuyOrderFailedResponse> Api::market_buy_order_failed() const {
    common::Params p;
    return create_stream<MarketBuyOrderFailedResponse>(
        *client_, "/web3_prediction_pm_market_buy_fail", p, std::nullopt);
}

common::WebsocketStream<MarketBuyOrderFullyFilledResponse>
Api::market_buy_order_fully_filled() const {
    common::Params p;
    return create_stream<MarketBuyOrderFullyFilledResponse>(
        *client_, "/web3_prediction_pm_market_buy_success", p, std::nullopt);
}

common::WebsocketStream<MarketResolutionNotificationResponse>
Api::market_resolution_notification() const {
    common::Params p;
    return create_stream<MarketResolutionNotificationResponse>(
        *client_, "/web3_prediction_pm_market_close", p, std::nullopt);
}

common::WebsocketStream<MarketSellOrderFailedExpiredResponse>
Api::market_sell_order_failed_expired() const {
    common::Params p;
    return create_stream<MarketSellOrderFailedExpiredResponse>(
        *client_, "/web3_prediction_pm_market_sell_fail", p, std::nullopt);
}

common::WebsocketStream<MarketSellOrderFullyFilledResponse>
Api::market_sell_order_fully_filled() const {
    common::Params p;
    return create_stream<MarketSellOrderFullyFilledResponse>(
        *client_, "/web3_prediction_pm_market_sell_success", p, std::nullopt);
}

common::WebsocketStream<PredictionOrderBookByMarketIdResponse>
Api::prediction_order_book_by_market_id(const PredictionOrderBookByMarketIdParams& params) const {
    common::Params p;
    common::detail::json::set_param(p, "marketId", params.market_id);
    return create_stream<PredictionOrderBookByMarketIdResponse>(
        *client_, "/web3_prediction_orderbook_<marketId>", p, std::nullopt);
}

common::WebsocketStream<RewardClaimFailedResponse> Api::reward_claim_failed() const {
    common::Params p;
    return create_stream<RewardClaimFailedResponse>(*client_, "/web3_prediction_pm_claim_fail", p,
                                                    std::nullopt);
}

common::WebsocketStream<RewardClaimSucceededResponse> Api::reward_claim_succeeded() const {
    common::Params p;
    return create_stream<RewardClaimSucceededResponse>(
        *client_, "/web3_prediction_pm_claim_success", p, std::nullopt);
}

} // namespace binance::w3w_prediction::websocket_streams
