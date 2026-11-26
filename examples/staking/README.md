# Binance Staking examples

One runnable program for every endpoint, grouped like the API: `rest_api/<api>/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=staking
cmake --build --preset dev
./build/dev/examples/staking/rest_api/eth_staking_api/eth_staking_account
```

Every example is its own executable under `build/<preset>/examples/staking/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials. Some of them change the account (place orders, transfer assets, ...): read the example
before running it.

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
