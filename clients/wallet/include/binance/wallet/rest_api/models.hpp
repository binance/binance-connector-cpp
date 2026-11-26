//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <binance/wallet/rest_api/models/account_api_trading_status_response.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data.hpp>
#include <binance/wallet/rest_api/models/account_api_trading_status_response_data_trigger_condition.hpp>
#include <binance/wallet/rest_api/models/account_info_response.hpp>
#include <binance/wallet/rest_api/models/account_status_response.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner.hpp>
#include <binance/wallet/rest_api/models/all_coins_information_response_inner_network_list_inner.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response_ctr.hpp>
#include <binance/wallet/rest_api/models/asset_detail_response_sky.hpp>
#include <binance/wallet/rest_api/models/asset_dividend_record_response.hpp>
#include <binance/wallet/rest_api/models/asset_dividend_record_response_rows_inner.hpp>
#include <binance/wallet/rest_api/models/broker_withdraw_response.hpp>
#include <binance/wallet/rest_api/models/check_questionnaire_requirements_response.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_assets_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_balances_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_position_inner.hpp>
#include <binance/wallet/rest_api/models/daily_account_snapshot_response_snapshot_vos_inner_data_user_assets_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_address_response.hpp>
#include <binance/wallet/rest_api/models/deposit_history_response_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_history_travel_rule_response_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner.hpp>
#include <binance/wallet/rest_api/models/deposit_history_v2_response_inner_questionnaire.hpp>
#include <binance/wallet/rest_api/models/dust_convert_response.hpp>
#include <binance/wallet/rest_api/models/dust_convert_response_transfer_result_inner.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response.hpp>
#include <binance/wallet/rest_api/models/dust_convertible_assets_response_details_inner.hpp>
#include <binance/wallet/rest_api/models/dust_transfer_response.hpp>
#include <binance/wallet/rest_api/models/dust_transfer_response_transfer_result_inner.hpp>
#include <binance/wallet/rest_api/models/dustlog_response.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner.hpp>
#include <binance/wallet/rest_api/models/dustlog_response_user_asset_dribblets_inner_user_asset_dribblet_details_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_address_verification_list_response_inner_address_questionnaire.hpp>
#include <binance/wallet/rest_api/models/fetch_deposit_address_list_with_network_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_address_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/fetch_withdraw_quota_response.hpp>
#include <binance/wallet/rest_api/models/funding_wallet_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_api_key_permission_response.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response.hpp>
#include <binance/wallet/rest_api/models/get_assets_that_can_be_converted_into_bnb_response_details_inner.hpp>
#include <binance/wallet/rest_api/models/get_cloud_mining_payment_and_refund_history_response.hpp>
#include <binance/wallet/rest_api/models/get_cloud_mining_payment_and_refund_history_response_rows_inner.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response.hpp>
#include <binance/wallet/rest_api/models/get_country_list_response_countries_inner.hpp>
#include <binance/wallet/rest_api/models/get_open_symbol_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response.hpp>
#include <binance/wallet/rest_api/models/get_region_list_response_regions_inner.hpp>
#include <binance/wallet/rest_api/models/get_spot_asset_tags_response_inner.hpp>
#include <binance/wallet/rest_api/models/get_symbols_delist_schedule_for_spot_response_inner.hpp>
#include <binance/wallet/rest_api/models/one_click_arrival_deposit_apply_response.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response.hpp>
#include <binance/wallet/rest_api/models/query_user_delegation_history_response_rows_inner.hpp>
#include <binance/wallet/rest_api/models/query_user_universal_transfer_history_response.hpp>
#include <binance/wallet/rest_api/models/query_user_universal_transfer_history_response_rows_inner.hpp>
#include <binance/wallet/rest_api/models/query_user_wallet_balance_response_inner.hpp>
#include <binance/wallet/rest_api/models/query_user_wallet_balance_response_inner_asset_balances_inner.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_response.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_travel_rule_response.hpp>
#include <binance/wallet/rest_api/models/submit_deposit_questionnaire_v2_response.hpp>
#include <binance/wallet/rest_api/models/system_status_response.hpp>
#include <binance/wallet/rest_api/models/toggle_bnb_burn_on_spot_trade_and_margin_interest_response.hpp>
#include <binance/wallet/rest_api/models/trade_fee_response_inner.hpp>
#include <binance/wallet/rest_api/models/user_asset_response_inner.hpp>
#include <binance/wallet/rest_api/models/user_universal_transfer_response.hpp>
#include <binance/wallet/rest_api/models/vasp_list_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_history_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_history_v1_response_inner.hpp>
#include <binance/wallet/rest_api/models/withdraw_response.hpp>
#include <binance/wallet/rest_api/models/withdraw_travel_rule_response.hpp>
