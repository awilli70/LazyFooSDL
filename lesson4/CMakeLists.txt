cmake_minimum_required(VERSION 3.31)
project(lesson4 VERSION 1.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED)

set(SOURCE_FILES
    src/main.cxx
)
file(COPY "src/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lesson4 ${SOURCE_FILES})
target_link_libraries(lesson4 SDL2::SDL2)
target_include_directories(lesson4 PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_options(lesson4 PRIVATE ${SDL2_CFLAGS})
