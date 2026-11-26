include(CMakePackageConfigHelpers)

get_property(_binance_product_targets GLOBAL PROPERTY BINANCE_PRODUCT_TARGETS)
get_property(_binance_product_include_dirs GLOBAL PROPERTY BINANCE_PRODUCT_INCLUDE_DIRS)
list(TRANSFORM _binance_product_include_dirs APPEND "/")

install(TARGETS binance_common ${_binance_product_targets}
    EXPORT binance-connector-cpp-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY
    "${PROJECT_SOURCE_DIR}/common/include/"
    "${PROJECT_BINARY_DIR}/common/include/"
    ${_binance_product_include_dirs}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp")

set(_binance_cmake_dir ${CMAKE_INSTALL_LIBDIR}/cmake/binance-connector-cpp)

install(EXPORT binance-connector-cpp-targets
    NAMESPACE binance::
    FILE binance-connector-cpp-targets.cmake
    DESTINATION ${_binance_cmake_dir})

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/binance-connector-cpp-config.cmake.in"
    "${PROJECT_BINARY_DIR}/binance-connector-cpp-config.cmake"
    INSTALL_DESTINATION ${_binance_cmake_dir})

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/binance-connector-cpp-config-version.cmake"
    # SemVer: only a major release breaks the API or ABI.
    COMPATIBILITY SameMajorVersion)

install(FILES
    "${PROJECT_BINARY_DIR}/binance-connector-cpp-config.cmake"
    "${PROJECT_BINARY_DIR}/binance-connector-cpp-config-version.cmake"
    DESTINATION ${_binance_cmake_dir})

install(FILES "${PROJECT_SOURCE_DIR}/LICENCE" DESTINATION ${CMAKE_INSTALL_DOCDIR})
