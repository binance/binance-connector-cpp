cmake_minimum_required(VERSION 3.24)

project(binance-connector-cpp
    VERSION 1.0.0
    DESCRIPTION "Binance public API connector for C++"
    HOMEPAGE_URL "https://github.com/binance/binance-connector-cpp"
    LANGUAGES CXX)

# The C++ ABI is kept only between patch releases (minor releases add fields to the generated
# structs), so the shared libraries carry <major>.<minor>; libbinance_c has its own C ABI version.
set(BINANCE_SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set(BINANCE_PRODUCTS "all" CACHE STRING
    "Products to build: \"all\", \"\" for common only, or names separated by \";\" or \",\"")
option(BINANCE_BUILD_TESTS "Build the test suites (needs GoogleTest)" OFF)
option(BINANCE_BUILD_EXAMPLES "Build the examples" OFF)
# Off by default, so that a newer compiler cannot break a consumer's build (vcpkg, distributions);
# the dev, ci and release-tests presets turn it on.
option(BINANCE_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(BINANCE_BUILD_C_API "Build the C interface (binance_c) for language bindings" OFF)
option(BINANCE_INSTALL "Generate install and package config rules" ${PROJECT_IS_TOP_LEVEL})

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
if(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "binance-connector-cpp requires C++20 or newer (CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD})")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    # DLLs next to the test executables, so that they run (and are listed) on Windows.
    if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(GNUInstallDirs)
include(BinanceWarnings)
include(BinanceLibrary)
include(BinanceProducts)
include(BinanceExamples)

find_package(Threads REQUIRED)
find_package(Boost 1.86 CONFIG REQUIRED COMPONENTS json)
find_package(OpenSSL 3.0 REQUIRED)
find_package(ZLIB REQUIRED)

if(BINANCE_BUILD_TESTS)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
endif()

if(BINANCE_BUILD_C_API)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
endif()

add_subdirectory(common)
binance_add_selected_products()

if(BINANCE_BUILD_C_API)
    add_subdirectory(c_api)
endif()

if(BINANCE_BUILD_EXAMPLES)
    binance_add_examples()
endif()

if(BINANCE_INSTALL)
    include(BinanceInstall)
endif()

message(STATUS "binance-connector-cpp ${PROJECT_VERSION}: products = ${BINANCE_SELECTED_PRODUCTS}")
