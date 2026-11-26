# An overlay port of the checkout it is in (`--overlay-ports=<checkout>/ports`): it builds that
# tree, so it always matches the commit.
get_filename_component(SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

set(products "")
foreach(feature IN LISTS FEATURES)
    if(feature STREQUAL "core" OR feature STREQUAL "all")
        continue()
    endif()
    string(REPLACE "-" "_" product "${feature}")
    list(APPEND products "${product}")
endforeach()
# Commas: a semicolon list would be split into several options on the way to CMake.
list(JOIN products "," BINANCE_PRODUCTS)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        "-DBINANCE_PRODUCTS=${BINANCE_PRODUCTS}"
        -DBINANCE_BUILD_TESTS=OFF
        -DBINANCE_BUILD_EXAMPLES=OFF
        -DBINANCE_BUILD_C_API=OFF
        -DBINANCE_WARNINGS_AS_ERRORS=OFF
        -DBINANCE_INSTALL=ON
)
vcpkg_cmake_install()
vcpkg_cmake_config_fixup(PACKAGE_NAME binance-connector-cpp CONFIG_PATH lib/cmake/binance-connector-cpp)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include" "${CURRENT_PACKAGES_DIR}/debug/share")
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENCE")
