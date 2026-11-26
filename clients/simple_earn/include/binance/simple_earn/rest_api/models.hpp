//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <binance/simple_earn/rest_api/models/get_bfusd_account_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_fast_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_standard_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_quota_details_response_subscription_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rate_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_redemption_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_redemption_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_rewards_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_subscription_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_bfusd_subscription_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_collateral_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_collateral_record_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_personal_left_quota_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_product_position_response_rows_inner_tier_annual_percentage_rate.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_redemption_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_redemption_record_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_rewards_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_preview_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_flexible_subscription_record_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_personal_left_quota_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_product_position_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_product_position_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_redemption_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_redemption_record_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_rewards_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_subscription_preview_response_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_subscription_record_response.hpp>
#include <binance/simple_earn/rest_api/models/get_locked_subscription_record_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rate_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_account_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_fast_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_standard_redemption_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_quota_details_response_subscription_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rate_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rate_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_redemption_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_redemption_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rewards_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_rewards_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_subscription_history_response.hpp>
#include <binance/simple_earn/rest_api/models/get_rwusd_subscription_history_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_flexible_product_list_response.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_flexible_product_list_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response_rows_inner.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response_rows_inner_detail.hpp>
#include <binance/simple_earn/rest_api/models/get_simple_earn_locked_product_list_response_rows_inner_quota.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response.hpp>
#include <binance/simple_earn/rest_api/models/get_yield_arena_activities_response_activities_inner.hpp>
#include <binance/simple_earn/rest_api/models/redeem_bfusd_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_flexible_product_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_locked_product_response.hpp>
#include <binance/simple_earn/rest_api/models/redeem_rwusd_response.hpp>
#include <binance/simple_earn/rest_api/models/set_flexible_auto_subscribe_response.hpp>
#include <binance/simple_earn/rest_api/models/set_locked_auto_subscribe_response.hpp>
#include <binance/simple_earn/rest_api/models/set_locked_product_redeem_option_response.hpp>
#include <binance/simple_earn/rest_api/models/simple_account_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_bfusd_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_flexible_product_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_locked_product_response.hpp>
#include <binance/simple_earn/rest_api/models/subscribe_rwusd_response.hpp>
