#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest)and enable_testing() already done in top CMakeLists.txt

add_executable(unitTests
attacks/AttackTest.cpp player/PlayerTest.cpp
 test_factory.cpp ItemTest.cpp
 ${CMAKE_SOURCE_DIR}/src/core/Weapons/Sword.cpp 
 ${CMAKE_SOURCE_DIR}/src/core/Weapons/Feather.cpp
 )

target_include_directories(unitTests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core/Factories
    ${CMAKE_SOURCE_DIR}/src/core/Weapons
)

target_link_libraries(unitTests GTest::gtest_main lib_core pugixml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# The next line enables CMake’s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module.
include(GoogleTest)
gtest_discover_tests(unitTests)
