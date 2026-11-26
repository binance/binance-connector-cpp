# Binance Derivatives Trading (COIN-M Futures) examples

One runnable program for every endpoint and stream, grouped like the API: `rest_api/<api>/<operation>.cpp`, `websocket_api/<api>/<operation>.cpp` and `websocket_streams/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=derivatives_trading_coin_futures
cmake --build --preset dev
./build/dev/examples/derivatives_trading_coin_futures/rest_api/market_data_api/basis
```

Every example is its own executable under `build/<preset>/examples/derivatives_trading_coin_futures/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials. The examples that place or cancel orders (security type `TRADE`) use the testnet, so that running them
places no real order: use the API keys of that environment, which are separate from the production ones. The other
examples that change the account (transfer assets, ...) run on production: read them before running them. To run any other example elsewhere, replace `production(...)` with `demo(...)` or `testnet(...)` in it
(their keys are separate).

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
