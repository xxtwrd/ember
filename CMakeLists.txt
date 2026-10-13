cmake_minimum_required(VERSION 3.14)
project(ember CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_executable(ember src/main.cpp src/memory.cpp src/dump.cpp)
target_include_directories(ember PRIVATE src)

