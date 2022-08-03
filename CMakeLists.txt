cmake_minimum_required(VERSION 3.16)

project(FromGraveToHeaven)

set(CMAKE_CXX_STANDART 17)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

set(raylib_DIR "C:/raylib/raylib/cmake")

find_package(raylib 4.0 QUIET)

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

file(GLOB src_files
  "*.h"
  "*.hpp"
  "src/main.cpp"
  "src/hud.cpp"
  "resources"
)

add_executable(${PROJECT_NAME} ${src_files})
set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)