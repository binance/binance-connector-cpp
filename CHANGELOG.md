# Changelog

## 2.0.0 - 2026-11-27

**Derivatives Trading COIN Futures**

### Added (8)

#### REST API

- `cancel_algo_order()` (`DELETE /dapi/v1/algoOrder`)
- `cancel_all_algo_open_orders()` (`DELETE /dapi/v1/algoOpenOrders`)
- `current_all_algo_open_orders()` (`GET /dapi/v1/openAlgoOrders`)
- `new_algo_order()` (`POST /dapi/v1/algoOrder`)
- `query_algo_order()` (`GET /dapi/v1/algoOrder`)
- `query_all_algo_orders()` (`GET /dapi/v1/allAlgoOrders`)

#### WebSocket API

- `cancel_algo_order()` (`algoOrder.cancel` method)
- `new_algo_order()` (`algoOrder.place` method)

### Changed (12)

#### REST API

- Added response schema `cancelAlgoOrderResponse`
- Added response schema `currentAllAlgoOpenOrdersResponse`
- Added response schema `cancelAllAlgoOpenOrdersResponse`
- Added response schema `queryAllAlgoOrdersResponse`
- Added response schema `queryAlgoOrderResponse`
- Added response schema `newAlgoOrderResponse`

#### WebSocket API

- Added response schema `cancelAlgoOrderResponse`
- Added response schema `newAlgoOrderResponse`

#### WebSocket Streams

- Added response schema `conditionalOrderTriggerReject`
- Added response schema `algoUpdate`
- Modified response schema `UserDataStreamEventsResponse`:
  - oneOf added 2 schema(s)

**Stocks**

### Added (2)

#### REST API

- `bstocks_corporate_action_records()` (`GET /sapi/v1/bstocks/corp-action/history`)
- `corporate_action_records()` (`GET /sapi/v1/equity/corp-action/history`)

### Removed (2)

#### REST API

- `bstocks_corporate_action_records()` (`GET /sapi/v1/bstocks/corp-action`)
- `corporate_action_records()` (`GET /sapi/v1/equity/corp-action`)

## 1.0.0 - 2026-11-26

- Initial release.
