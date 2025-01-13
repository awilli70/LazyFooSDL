cmake_minimum_required(VERSION 3.31)
project(lesson1 VERSION 1.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED)

set(SOURCE_FILES
    src/main.cxx
)

add_executable(lesson1 ${SOURCE_FILES})
target_link_libraries(lesson1 SDL2::SDL2)
target_include_directories(lesson1 PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_options(lesson1 PRIVATE ${SDL2_CFLAGS})
