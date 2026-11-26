# The C interface: one shared library (binance_c) that bundles binance::common.
if(MSVC)
    string(REPLACE "/EHsc" "/EHs" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    if(NOT CMAKE_CXX_FLAGS MATCHES "/EH")
        string(APPEND CMAKE_CXX_FLAGS " /EHs")
    endif()
endif()
add_library(binance_c SHARED src/binance_c.cpp)
# The SONAME follows the C ABI (BNC_ABI_VERSION in binance_c.h), not the SDK version: it changes
# exactly when the header changes incompatibly.
file(STRINGS include/binance/binance_c.h _bnc_abi_line REGEX "^#define BNC_ABI_VERSION [0-9]+$")
string(REGEX REPLACE "^#define BNC_ABI_VERSION " "" BNC_ABI_VERSION "${_bnc_abi_line}")
if(NOT BNC_ABI_VERSION MATCHES "^[0-9]+$")
    message(FATAL_ERROR "binance_c: BNC_ABI_VERSION not found in include/binance/binance_c.h")
endif()
add_library(binance::c ALIAS binance_c)
target_include_directories(binance_c PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_definitions(binance_c PRIVATE BINANCE_C_BUILDING)
target_link_libraries(binance_c PRIVATE binance::common $<BUILD_INTERFACE:binance_warnings>)
set_target_properties(binance_c PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${BNC_ABI_VERSION}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    POSITION_INDEPENDENT_CODE ON)
# Only bnc_* is exported: not common, Boost or the bundled OpenSSL.
if(APPLE)
    target_link_options(binance_c PRIVATE "LINKER:-exported_symbol,_bnc_*")
elseif(NOT MSVC)
    target_link_options(binance_c PRIVATE LINKER:--exclude-libs,ALL)
    # Self-contained by default: the C++ runtime is inside the library. OFF for a GCC Toolset build
    # (manylinux), whose own runtime is split between the library and the system libstdc++.so.6.
    option(BINANCE_C_STATIC_CXX_RUNTIME "Link the C++ runtime statically into binance_c" ON)
    if(BINANCE_C_STATIC_CXX_RUNTIME)
        target_link_options(binance_c PRIVATE -static-libstdc++ -static-libgcc)
    endif()
endif()
# Windows: the DLL (binance_c.dll, exporting bnc_* through BNC_API) should not need the Visual C++
# redistributable. With a static vcpkg triplet, configure with
# -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded so that every target uses the static runtime.
if(MSVC AND VCPKG_TARGET_TRIPLET MATCHES "-static$" AND NOT CMAKE_MSVC_RUNTIME_LIBRARY MATCHES "^MultiThreaded")
    message(WARNING "binance_c: the vcpkg triplet ${VCPKG_TARGET_TRIPLET} is static, but "
                    "CMAKE_MSVC_RUNTIME_LIBRARY is '${CMAKE_MSVC_RUNTIME_LIBRARY}': the DLL would mix runtimes. "
                    "Pass -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded.")
endif()

if(BINANCE_INSTALL)
    install(TARGETS binance_c
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(FILES include/binance/binance_c.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/binance)
endif()

if(BINANCE_BUILD_TESTS)
    add_executable(binance_c_tests tests/c_api_test.cpp)
    target_include_directories(binance_c_tests PRIVATE ${PROJECT_SOURCE_DIR}/common/tests)
    target_link_libraries(binance_c_tests
        PRIVATE binance::c binance::common GTest::gtest_main $<BUILD_INTERFACE:binance_warnings>)
    gtest_discover_tests(binance_c_tests
        TEST_PREFIX "c_api." DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 60)
endif()
