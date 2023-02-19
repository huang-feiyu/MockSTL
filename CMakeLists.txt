cmake_minimum_required(VERSION 3.23)
project(mock_stl)

set(CMAKE_CXX_STANDARD 17)

# === Fetch Google Test ===
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# === Sample Test === TODO: Remove this and add general test directory
enable_testing()

add_executable(
        main
        main.cpp
)
target_link_libraries(
        main
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main)
