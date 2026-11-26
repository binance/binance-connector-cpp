include(CheckIPOSupported)

option(BINANCE_LTO "Link-time optimisation of shared Release builds" ON)
if(BINANCE_LTO AND BUILD_SHARED_LIBS)
    check_ipo_supported(RESULT _binance_ipo_supported OUTPUT _binance_ipo_error LANGUAGES CXX)
    if(NOT _binance_ipo_supported)
        message(STATUS "LTO disabled: ${_binance_ipo_error}")
    endif()
endif()

# binance_configure_library(<target> <BASE_NAME>): export macros and Release size settings.
# Static libraries skip LTO: their objects would only link with the same compiler.
function(binance_configure_library target base_name)
    set(_release "$<CONFIG:Release,MinSizeRel>")
    if(MSVC)
        target_compile_options(${target} PUBLIC /bigobj)
        target_compile_options(${target} PRIVATE "$<${_release}:/Gy;/Gw>")
    else()
        target_compile_options(${target} PRIVATE
            "$<${_release}:-ffunction-sections;-fdata-sections>")
    endif()

    if(NOT BUILD_SHARED_LIBS)
        target_compile_definitions(${target} PUBLIC ${base_name}_STATIC_DEFINE)
        return()
    endif()

    set_target_properties(${target} PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON)
    if(MSVC)
        # Exported classes hold standard-library members: the DLL and its users must share the
        # same toolset and runtime.
        target_compile_options(${target} PUBLIC /wd4251)
    endif()
    if(APPLE)
        target_link_options(${target} PRIVATE $<${_release}:LINKER:-dead_strip>)
    elseif(NOT MSVC)
        target_link_options(${target} PRIVATE
            LINKER:--exclude-libs,ALL $<${_release}:LINKER:--gc-sections>)
    endif()
    if(_binance_ipo_supported)
        set_target_properties(${target} PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION_RELEASE ON
            INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL ON)
    endif()
endfunction()
