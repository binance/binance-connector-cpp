# Internal (non-exported) target carrying the project's warning flags.
add_library(binance_warnings INTERFACE)

if(MSVC)
    target_compile_options(binance_warnings INTERFACE /W4 /permissive- /utf-8)
    target_compile_definitions(binance_warnings INTERFACE _CRT_SECURE_NO_WARNINGS)
    if(BINANCE_WARNINGS_AS_ERRORS)
        target_compile_options(binance_warnings INTERFACE /WX)
    endif()
else()
    target_compile_options(binance_warnings INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wnon-virtual-dtor)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_FLAGS MATCHES "-fsanitize=")
        target_compile_options(binance_warnings INTERFACE -Wno-maybe-uninitialized)
    endif()
    if(BINANCE_WARNINGS_AS_ERRORS)
        target_compile_options(binance_warnings INTERFACE -Werror)
    endif()
endif()
