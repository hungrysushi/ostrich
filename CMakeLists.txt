cmake_minimum_required(VERSION 3.0)
project(gb_ostrich)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(gb_ostrich
    main.cpp
    src/cart.cpp
    )

target_include_directories(gb_ostrich PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
