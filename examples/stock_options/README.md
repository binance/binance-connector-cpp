# Binance Stock Option Trading examples

One runnable program for every endpoint and stream, grouped like the API: `rest_api/<api>/<operation>.cpp` and `websocket_streams/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=stock_options
cmake --build --preset dev
./build/dev/examples/stock_options/rest_api/market_data_api/option_contracts
```

Every example is its own executable under `build/<preset>/examples/stock_options/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials. Some of them change the account (place orders, transfer assets, ...): read the example
before running it.

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
