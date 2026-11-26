//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <binance/derivatives_trading_options/rest_api/models/accept_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/accept_block_trade_order_response_legs_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_block_trade_list_response_inner_legs_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_funding_flow_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/account_trade_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_all_option_orders_by_underlying_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_all_option_orders_on_specific_symbol_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_multiple_option_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/cancel_option_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/check_server_time_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_assets_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_contracts_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_option_symbols_inner_filters_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/exchange_information_response_rate_limits_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/extend_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/extend_block_trade_order_response_legs_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/get_auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/get_market_maker_protection_config_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/historical_exercise_records_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/index_price_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/kline_candlestick_data_item_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_legs_parameter_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_block_trade_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/new_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/open_interest_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_asset_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_margin_account_information_response_greek_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_mark_price_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/option_position_information_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/order_book_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_orders_parameter_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/place_multiple_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_details_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_details_response_legs_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_block_trade_order_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_current_open_option_orders_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_option_order_history_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/query_single_order_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/recent_block_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/recent_trades_list_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/reset_market_maker_protection_config_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/set_auto_cancel_all_open_orders_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/set_market_maker_protection_config_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/start_user_data_stream_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/ticker24hr_price_change_statistics_response_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/tradfi_options_contract_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_commission_response.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_commission_response_commissions_inner.hpp>
#include <binance/derivatives_trading_options/rest_api/models/user_exercise_record_response_inner.hpp>
