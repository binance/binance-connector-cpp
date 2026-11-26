//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#include <future>

#include <boost/asio/bind_cancellation_slot.hpp>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/use_future.hpp>

#include <binance/common/errors.hpp>
#include <binance/common/websocket_stream.hpp>

#include "websocket_common.hpp"

namespace binance::common {

WebsocketStreamHandle::WebsocketStreamHandle(std::string stream,
                                             std::shared_ptr<detail::StreamBinding> binding)
    : state_(std::make_shared<State>()) {
    state_->stream = std::move(stream);
    state_->binding = std::move(binding);
}

WebsocketStreamHandle& WebsocketStreamHandle::operator=(WebsocketStreamHandle&& other) noexcept {
    if (this != &other) {
        unsubscribe(false);
        state_ = std::move(other.state_);
    }
    return *this;
}

WebsocketStreamHandle::~WebsocketStreamHandle() {
    unsubscribe(false);
}

const std::string& WebsocketStreamHandle::stream() const noexcept {
    static const std::string empty;
    return state_ ? state_->stream : empty;
}

void WebsocketStreamHandle::add(detail::Callback<boost::json::value> callback) {
    if (!state_ || !state_->binding) {
        return;
    }
    auto slot = std::make_shared<detail::StreamSlot>(std::move(callback));
    {
        const std::lock_guard lock(state_->mutex);
        if (state_->unsubscribed) {
            return;
        }
        state_->slots.push_back(slot);
    }
    state_->binding->add(std::move(slot));
}

void WebsocketStreamHandle::unsubscribe() noexcept {
    unsubscribe(true);
}

void WebsocketStreamHandle::unsubscribe(bool wait) noexcept {
    if (!state_ || !state_->binding) {
        return;
    }
    std::vector<std::shared_ptr<detail::StreamSlot>> slots;
    {
        const std::lock_guard lock(state_->mutex);
        if (std::exchange(state_->unsubscribed, true)) {
            return;
        }
        slots = std::exchange(state_->slots, {});
    }
    for (const auto& slot : slots) {
        slot->active = false;
    }
    if (wait) {
        detail::wait_until_idle(slots);
    }
    try {
        state_->binding->remove(std::move(slots), wait);
    } catch (const std::exception& e) {
        Logger::error(std::string("Failed to unsubscribe: ") + e.what());
    }
}

void WebsocketStreamHandle::release() noexcept {
    state_.reset();
}

void WebsocketStreamHandle::start_wait_subscribed(
    const std::shared_ptr<State>& state,
    boost::asio::any_completion_handler<void(std::exception_ptr)> handler) {
    bool active = state && state->binding;
    if (active) {
        const std::lock_guard lock(state->mutex);
        active = !state->unsubscribed;
    }
    if (!active) {
        detail::complete_later(std::move(handler),
                               std::make_exception_ptr(WebsocketCancelledError()));
        return;
    }
    state->binding->wait_subscribed(std::move(handler));
}

void WebsocketStreamHandle::wait_subscribed(std::optional<std::chrono::milliseconds> timeout) {
    if (state_ && state_->binding && !state_->binding->may_block()) {
        throw detail::blocking_call_error("wait_subscribed", "async_wait_subscribed");
    }
    if (!timeout) {
        async_wait_subscribed(boost::asio::use_future).get();
        return;
    }
    boost::asio::cancellation_signal signal;
    auto done = async_wait_subscribed(
        boost::asio::bind_cancellation_slot(signal.slot(), boost::asio::use_future));
    if (done.wait_for(*timeout) == std::future_status::timeout) {
        signal.emit(boost::asio::cancellation_type::terminal);
        try {
            done.get();
        } catch (const WebsocketCancelledError&) {
            throw WebsocketTimeoutError();
        }
        return; // acknowledged just before the cancellation took effect
    }
    done.get();
}

} // namespace binance::common
