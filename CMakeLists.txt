cmake_minimum_required(VERSION 3.31)

# Name of executable
project(bf_interp)

# {{{ ===== CMAKE SETTINGS =====

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# }}}

# {{{ ===== BUILD MODES =====

#### Debug ####

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0 -fno-omit-frame-pointer)
    add_compile_options(
        -fsanitize=address,undefined
        -fsanitize-recover=address
        -fno-omit-frame-pointer
        -g
        -O0
    )
    add_link_options(
        -fsanitize=address,undefined
    )
endif()

#### Dev ####

if (CMAKE_BUILD_TYPE STREQUAL "Dev")
    add_compile_options(-g -O2 -fno-omit-frame-pointer -U NDEBUG)
endif()

#### Release ####

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-g -O3 -ffast-math -DNDEBUG)
endif()

# }}}

add_executable(${CMAKE_PROJECT_NAME}
    src/main.c
)
