//
// Binance C++ Connector
// https://github.com/binance/binance-connector-cpp
//
// Distributed under the MIT License. See the LICENCE file.
// Documentation: https://binance.github.io/binance-connector-cpp/
//

#pragma once

#include <binance/staking/rest_api/models/claim_boost_rewards_response.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response_holdings.hpp>
#include <binance/staking/rest_api/models/eth_staking_account_response_profit.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rate_history_response_rows_inner_boost_rewards_inner.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_bnsol_rewards_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_boost_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_boost_rewards_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_current_eth_staking_quota_response.hpp>
#include <binance/staking/rest_api/models/get_eth_redemption_history_response.hpp>
#include <binance/staking/rest_api/models/get_eth_redemption_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_eth_staking_history_response.hpp>
#include <binance/staking/rest_api/models/get_eth_staking_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_personal_left_quota_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner_detail.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_list_response_rows_inner_quota.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_position_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_product_position_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_redemption_record_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_redemption_record_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_rewards_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_preview_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_record_response.hpp>
#include <binance/staking/rest_api/models/get_on_chain_yields_locked_subscription_record_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_product_list_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_soft_staking_rewards_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_sol_redemption_history_response.hpp>
#include <binance/staking/rest_api/models/get_sol_redemption_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_history_response.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_sol_staking_quota_details_response.hpp>
#include <binance/staking/rest_api/models/get_unclaimed_rewards_response_inner.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rate_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rate_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_rewards_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_wbeth_unwrap_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_unwrap_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/get_wbeth_wrap_history_response.hpp>
#include <binance/staking/rest_api/models/get_wbeth_wrap_history_response_rows_inner.hpp>
#include <binance/staking/rest_api/models/on_chain_yields_account_response.hpp>
#include <binance/staking/rest_api/models/redeem_eth_response.hpp>
#include <binance/staking/rest_api/models/redeem_on_chain_yields_locked_product_response.hpp>
#include <binance/staking/rest_api/models/redeem_sol_response.hpp>
#include <binance/staking/rest_api/models/set_on_chain_yields_locked_auto_subscribe_response.hpp>
#include <binance/staking/rest_api/models/set_on_chain_yields_locked_product_redeem_option_response.hpp>
#include <binance/staking/rest_api/models/set_soft_staking_response.hpp>
#include <binance/staking/rest_api/models/sol_staking_account_response.hpp>
#include <binance/staking/rest_api/models/subscribe_eth_staking_response.hpp>
#include <binance/staking/rest_api/models/subscribe_on_chain_yields_locked_product_response.hpp>
#include <binance/staking/rest_api/models/subscribe_sol_staking_response.hpp>
#include <binance/staking/rest_api/models/wrap_beth_response.hpp>
