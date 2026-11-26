//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <binance/w3w_prediction/rest_api/models/apply_mm_deposit_response.hpp>
#include <binance/w3w_prediction/rest_api/models/apply_mm_withdraw_response.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_cancel_info_list_parameter_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_response.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_cancel_orders_response_failed_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response.hpp>
#include <binance/w3w_prediction/rest_api/models/batch_redeem_response_results_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/create_inbound_transfer_response.hpp>
#include <binance/w3w_prediction/rest_api/models/create_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/create_outbound_transfer_response.hpp>
#include <binance/w3w_prediction/rest_api/models/fulfil_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_markets_inner_outcomes_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_timeline_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_market_detail_response_variant_data.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_detail_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_detail_response_order_data.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_events_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_blocktrade_events_response_events_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_assets_parameter_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_otc_reserved_balances_response_balances_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_portfolio_response_positions_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/get_position_by_token_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_position_by_token_response_position.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quota_status_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_quote_response.hpp>
#include <binance/w3w_prediction/rest_api/models/get_redeem_status_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_otc_blocktrades_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_otc_blocktrades_response_blocktrades_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response_categories_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_categories_response_categories_inner_subcategories_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_markets_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_markets_response_market_topics_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_wallets_response.hpp>
#include <binance/w3w_prediction/rest_api/models/list_prediction_wallets_response_wallets_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/market_search_response_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/place_order_response.hpp>
#include <binance/w3w_prediction/rest_api/models/preview_otc_blocktrade_response.hpp>
#include <binance/w3w_prediction/rest_api/models/preview_otc_blocktrade_response_order_data.hpp>
#include <binance/w3w_prediction/rest_api/models/query_active_orders_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_active_orders_response_orders_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_last_trade_price_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response_asks_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_book_response_bids_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_history_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_order_history_response_orders_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_payment_option_balances_response_items_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_pnl_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_by_filter_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_by_filter_response_positions_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_counts.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_positions_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_positions_response_summary.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_settled_position_history_response_positions_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_list_response.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_list_response_transfers_inner.hpp>
#include <binance/w3w_prediction/rest_api/models/query_transfer_status_response.hpp>
#include <binance/w3w_prediction/rest_api/models/remove_otc_blocktrades_response.hpp>
