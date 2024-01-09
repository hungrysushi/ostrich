cmake_minimum_required(VERSION 3.0)
project(gb_ostrich)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(gb_ostrich
    main.cpp
    src/address_bus.cpp
    src/cart.cpp
    src/cpu.cpp
    src/io.cpp
    src/ppu.cpp
    src/timer.cpp
    )

target_include_directories(gb_ostrich PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

add_subdirectory(external/spdlog)
target_link_libraries(gb_ostrich PRIVATE spdlog::spdlog_header_only)

add_subdirectory(external/SDL)
if (TARGET SDL2::SDL2main)
    target_link_libraries(gb_ostrich PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(gb_ostrich PRIVATE SDL2::SDL2)
