cmake_minimum_required(VERSION 3.26)

include(FetchContent)
project(Corrige3_SimpleGame VERSION 1.0.0 LANGUAGES CXX)

if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

fetchContent_Declare( sfml
  URL https://github.com/SFML/SFML/archive/refs/tags/3.0.2.tar.gz
)
option(SFML_BUILD_AUDIO "Build audio" ON)
option(SFML_BUILD_NETWORK "Build network" ON)
FetchContent_MakeAvailable(sfml)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src/core)
add_subdirectory(src/main)

#
# Include GoogleTest
#
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable_testing() must be in the source directory root (see cmake documentation at https://cmake.org/cmake/help/latest/command/enable_testing.html)
# Otherwise, Visual Studio test explorer does not see unit tests (See ticket https://developercommunity.visualstudio.com/t/No-tests-discovered-for-googletest-and-C/1148799#T-ND1150621)
include(GoogleTest)
enable_testing()
#add_subdirectory(src/test)

option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)

