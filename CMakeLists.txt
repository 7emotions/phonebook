cmake_minimum_required(VERSION 3.22)
project(phonebook)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Werror -pedantic-errors)
    add_compile_options(-Wno-error=unused -Wno-error=unused-variable)
    add_compile_options(-Wno-error=unused-but-set-variable -Wno-error=unused-function -Wno-unused-parameter)
endif()

# Headers
include_directories(src)
file(GLOB_RECURSE PROJECT_INC src/*.hpp)

# Source
file(GLOB_RECURSE PROJECT_SRC src/*.cpp)


add_executable(${PROJECT_NAME} ${PROJECT_SRC} ${PROJECT_INC})
