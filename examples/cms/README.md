# Binance CMS examples

One runnable program for every endpoint and stream, grouped like the API: `websocket_streams/<operation>.cpp`.

Build them with the `dev` preset (or any preset with `-DBINANCE_BUILD_EXAMPLES=ON`), from the root of the
repository:

```bash
cmake --preset dev -DBINANCE_PRODUCTS=cms
cmake --build --preset dev
./build/dev/examples/cms/websocket_streams/com_announcement_en
```

Every example is its own executable under `build/<preset>/examples/cms/`, named after its file.

The examples read `API_KEY` and `API_SECRET` from the environment. They use the production endpoints, and an example that is signed refuses to start without
credentials.

Set `LOG_LEVEL=debug` to see the requests and the WebSocket traffic.
