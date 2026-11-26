include(GenerateExportHeader)

add_library(binance_common
    src/config.cpp
    src/decimal.cpp
    src/errors.cpp
    src/logger.cpp
    src/net.cpp
    src/rest.cpp
    src/signer.cpp
    src/tls.cpp
    src/utils.cpp
    src/version.cpp
    src/websocket_api.cpp
    src/websocket_common.cpp
    src/websocket_stream.cpp
    src/websocket_streams.cpp)
add_library(binance::common ALIAS binance_common)

set_target_properties(binance_common PROPERTIES
    EXPORT_NAME common
    OUTPUT_NAME binance_common
    VERSION ${PROJECT_VERSION}
    SOVERSION ${BINANCE_SOVERSION})

set(_binance_common_generated "${CMAKE_CURRENT_BINARY_DIR}/include")
configure_file(include/binance/common/version.hpp.in
    "${_binance_common_generated}/binance/common/version.hpp" @ONLY)
generate_export_header(binance_common
    BASE_NAME BINANCE_COMMON
    EXPORT_FILE_NAME "${_binance_common_generated}/binance/common/export.hpp")

target_include_directories(binance_common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${_binance_common_generated}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(binance_common PUBLIC cxx_std_20)
target_link_libraries(binance_common
    PUBLIC
        Boost::headers
        Boost::json
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB
        Threads::Threads
    PRIVATE
        $<BUILD_INTERFACE:binance_warnings>)
target_include_directories(binance_common PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# No BOOST_ASIO_NO_DEPRECATED: it changes Asio's types, so it would have to be PUBLIC (imposed on
# every consumer) to keep the ODR. Asio config macros are left to the application.
if(WIN32)
    target_link_libraries(binance_common PRIVATE crypt32)
    target_compile_definitions(binance_common PUBLIC _WIN32_WINNT=0x0A00)
endif()

binance_configure_library(binance_common BINANCE_COMMON)

if(BINANCE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
