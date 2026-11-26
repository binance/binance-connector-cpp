# Binance C2C examples

One runnable program for every endpoint, grouped like the API: `rest_api/<api>/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=c2c
cmake --build --preset dev
./build/dev/examples/c2c/rest_api/get_c2c_trade_history
```

Every example is its own executable under `build/<preset>/examples/c2c/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials.

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
