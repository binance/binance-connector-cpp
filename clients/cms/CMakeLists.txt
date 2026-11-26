binance_add_product(cms
    SOURCES
        src/cms.cpp
        src/websocket_streams/api.cpp
        src/websocket_streams/models/com_announcement_en_response.cpp
        src/websocket_streams/websocket_streams.cpp
    TESTS
        tests/websocket_streams/api_test.cpp)
