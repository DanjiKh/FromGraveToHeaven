cmake_minimum_required(VERSION 3.16)

project(FromGraveToHeaven)

set(CMAKE_CXX_STANDART 17)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

set(raylib_DIR "C:/raylib/raylib/cmake")

if (NOT raylib_FOUND)
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
  "src/game.cpp"
  "src/game_screen.cpp"
  "src/objects.cpp"
  "src/resources_loading.cpp"
  "src/animated_sprites.cpp"
  "resources"
)

add_executable(${PROJECT_NAME} ${src_files})
set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)