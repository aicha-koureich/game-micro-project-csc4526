#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: include(GoogleTest)and enable_testing() already done in top CMakeLists.txt

add_executable(unitTests
        RoundTargetTest.cpp
)
target_link_libraries(unitTests GTest::gtest_main lib_core sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# The next line enables CMake’s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module.
include(GoogleTest)
gtest_discover_tests(unitTests)
