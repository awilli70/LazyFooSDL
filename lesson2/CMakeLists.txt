cmake_minimum_required(VERSION 3.31)
project(lession2 VERSION 1.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
find_package(SDL2 REQUIRED)

set(SOURCE_FILES
    src/main.cxx
)
file(COPY "src/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(lession2 ${SOURCE_FILES})
target_link_libraries(lession2 SDL2::SDL2)
target_include_directories(lession2 PRIVATE ${SDL2_INCLUDE_DIRS})
target_compile_options(lession2 PRIVATE ${SDL2_CFLAGS})
