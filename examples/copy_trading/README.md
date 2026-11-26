# Binance Copy Trading examples

One runnable program for every endpoint, grouped like the API: `rest_api/<api>/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=copy_trading
cmake --build --preset dev
./build/dev/examples/copy_trading/rest_api/future_copy_trading_api/get_futures_lead_trader_status
```

Every example is its own executable under `build/<preset>/examples/copy_trading/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials. Some of them change the account (place orders, transfer assets, ...): read the example
before running it.

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
