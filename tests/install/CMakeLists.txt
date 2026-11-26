# Builds against the installed package (find_package, every product component) to verify what
# `cmake --install` produces: headers, the config file, its dependencies and the export macros.
cmake_minimum_required(VERSION 3.24)
project(binance-connector-cpp-install-check LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(binance-connector-cpp CONFIG REQUIRED)
# Again, now that the installed products are known, to check them as components.
find_package(binance-connector-cpp CONFIG REQUIRED COMPONENTS ${binance-connector-cpp_PRODUCTS})

set(_includes "")
set(_names "")
foreach(_product IN LISTS binance-connector-cpp_PRODUCTS)
    string(APPEND _includes "#include <binance/${_product}/${_product}.hpp>\n")
    string(APPEND _names "binance::${_product}::product_name(), ")
endforeach()
file(CONFIGURE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/products.cpp" CONTENT [=[
#include <string_view>
#include <vector>

@_includes@
std::vector<std::string_view> installed_products() { return {@_names@}; }
]=] @ONLY)

add_executable(install_check main.cpp "${CMAKE_CURRENT_BINARY_DIR}/products.cpp")
target_link_libraries(install_check PRIVATE binance::common)
foreach(_product IN LISTS binance-connector-cpp_PRODUCTS)
    target_link_libraries(install_check PRIVATE binance::${_product})
endforeach()
