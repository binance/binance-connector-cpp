# Product discovery and selection.

include(GenerateExportHeader)

# Every directory under clients/ that contains a CMakeLists.txt is a product. The set that gets
# built is controlled by BINANCE_PRODUCTS ("all", a list of names, or "" for common only). Each
# product calls binance_add_product() from its own CMakeLists.txt.

file(GLOB _binance_product_dirs LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/clients/*")
set(BINANCE_AVAILABLE_PRODUCTS "")
foreach(_dir IN LISTS _binance_product_dirs)
    if(IS_DIRECTORY "${_dir}" AND EXISTS "${_dir}/CMakeLists.txt")
        get_filename_component(_name "${_dir}" NAME)
        list(APPEND BINANCE_AVAILABLE_PRODUCTS "${_name}")
    endif()
endforeach()
list(SORT BINANCE_AVAILABLE_PRODUCTS)

# Semicolons or commas: commas survive tools that split on `;` (e.g. vcpkg ports).
string(REPLACE "," ";" _binance_requested "${BINANCE_PRODUCTS}")
list(TRANSFORM _binance_requested STRIP)
list(FILTER _binance_requested EXCLUDE REGEX "^$")
string(TOLOWER "${_binance_requested}" _binance_requested_lower)
if(_binance_requested_lower STREQUAL "all")
    set(BINANCE_SELECTED_PRODUCTS ${BINANCE_AVAILABLE_PRODUCTS})
else()
    set(BINANCE_SELECTED_PRODUCTS ${_binance_requested})
    list(REMOVE_DUPLICATES BINANCE_SELECTED_PRODUCTS)
    foreach(_name IN LISTS BINANCE_SELECTED_PRODUCTS)
        if(NOT _name IN_LIST BINANCE_AVAILABLE_PRODUCTS)
            message(FATAL_ERROR
                "Unknown product '${_name}'. Available products: ${BINANCE_AVAILABLE_PRODUCTS}")
        endif()
    endforeach()
endif()

# binance_add_product(<name> SOURCES <src>... [TESTS <test-src>...])
#
# Creates the library binance_<name> (alias binance::<name>) linked against binance::common, with
# public headers under clients/<name>/include, and an optional GoogleTest executable.
function(binance_add_product name)
    cmake_parse_arguments(PARSE_ARGV 1 arg "" "" "SOURCES;TESTS")

    set(target binance_${name})
    add_library(${target} ${arg_SOURCES})
    add_library(binance::${name} ALIAS ${target})
    set_target_properties(${target} PROPERTIES
        EXPORT_NAME ${name}
        OUTPUT_NAME binance_${name}
        VERSION ${PROJECT_VERSION}
        SOVERSION ${BINANCE_SOVERSION})
    set(generated "${CMAKE_CURRENT_BINARY_DIR}/include")
    string(TOUPPER "${name}" upper)
    generate_export_header(${target}
        BASE_NAME BINANCE_${upper}
        EXPORT_FILE_NAME "${generated}/binance/${name}/export.hpp")
    target_include_directories(${target} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${generated}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
    binance_configure_library(${target} BINANCE_${upper})
    target_link_libraries(${target}
        PUBLIC binance::common
        PRIVATE $<BUILD_INTERFACE:binance_warnings>)
    target_compile_features(${target} PUBLIC cxx_std_20)

    set_property(GLOBAL APPEND PROPERTY BINANCE_PRODUCT_TARGETS ${target})
    set_property(GLOBAL APPEND PROPERTY BINANCE_PRODUCT_INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/include" "${generated}")

    if(BINANCE_BUILD_TESTS AND arg_TESTS)
        add_executable(${target}_tests ${arg_TESTS})
        target_link_libraries(${target}_tests
            PRIVATE ${target} GTest::gtest_main $<BUILD_INTERFACE:binance_warnings>)
        # Shared test helpers (mock servers, keys, certificates).
        target_include_directories(${target}_tests PRIVATE "${PROJECT_SOURCE_DIR}/common/tests")
        gtest_discover_tests(${target}_tests
            TEST_PREFIX "${name}." DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 60)
    endif()
endfunction()

function(binance_add_selected_products)
    foreach(_name IN LISTS BINANCE_SELECTED_PRODUCTS)
        add_subdirectory("${PROJECT_SOURCE_DIR}/clients/${_name}"
            "${PROJECT_BINARY_DIR}/clients/${_name}")
    endforeach()
endfunction()
