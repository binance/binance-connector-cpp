add_executable(binance_common_tests
    config_test.cpp
    connect_test.cpp
    decimal_test.cpp
    dependencies_test.cpp
    query_string_test.cpp
    required_test.cpp
    signer_test.cpp
    rest_test.cpp
    socks_test.cpp
    utils_test.cpp
    version_test.cpp
    websocket_test.cpp
    websocket_utils_test.cpp)
target_include_directories(binance_common_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(binance_common_tests
    PRIVATE binance::common GTest::gtest_main $<BUILD_INTERFACE:binance_warnings>)
# PRE_TEST: listing the tests at build time fails builds on macOS, whose first launch of a freshly
# linked binary can stall.
gtest_discover_tests(binance_common_tests
    TEST_PREFIX "common." DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 60)
