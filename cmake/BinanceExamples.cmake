function(binance_add_examples)
    set(_root "${PROJECT_SOURCE_DIR}/examples")
    foreach(_product IN LISTS BINANCE_SELECTED_PRODUCTS)
        file(GLOB_RECURSE _sources CONFIGURE_DEPENDS "${_root}/${_product}/*.cpp")
        foreach(_source IN LISTS _sources)
            file(RELATIVE_PATH _rel "${_root}" "${_source}")
            string(REGEX REPLACE "\\.cpp$" "" _path "${_rel}")
            # Short target names keep the object paths under MAX_PATH on Windows; the executable
            # keeps its readable name, and Ninja also builds it by path (examples/<path>).
            string(MD5 _hash "${_path}")
            string(SUBSTRING "${_hash}" 0 10 _hash)
            set(_name "example_${_hash}")
            add_executable(${_name} "${_source}")
            target_link_libraries(${_name} PRIVATE binance::${_product}
                $<BUILD_INTERFACE:binance_warnings>)
            get_filename_component(_dir "${_rel}" DIRECTORY)
            get_filename_component(_file "${_rel}" NAME_WE)
            set_target_properties(${_name} PROPERTIES
                OUTPUT_NAME "${_file}"
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/examples/${_dir}"
                PROJECT_LABEL "example ${_path}")
            target_compile_options(${_name} PRIVATE
                $<IF:$<CXX_COMPILER_ID:MSVC>,/wd4996,-Wno-deprecated-declarations>)
            if(WIN32 AND BUILD_SHARED_LIBS)
                add_custom_command(TARGET ${_name} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                        $<TARGET_RUNTIME_DLLS:${_name}> $<TARGET_FILE_DIR:${_name}>
                    COMMAND_EXPAND_LISTS)
            endif()
            # Drops the unused code of the static libraries (MSVC does by default).
            if(APPLE)
                target_link_options(${_name} PRIVATE
                    $<$<CONFIG:Release,MinSizeRel>:LINKER:-dead_strip>)
            elseif(NOT MSVC)
                target_link_options(${_name} PRIVATE
                    $<$<CONFIG:Release,MinSizeRel>:LINKER:--gc-sections>)
            endif()
        endforeach()
    endforeach()
endfunction()
