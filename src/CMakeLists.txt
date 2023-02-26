include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# === test cases ===
include(GoogleTest)

add_executable(vector_test vector_test.cpp)
target_link_libraries(vector_test gtest_main)
gtest_discover_tests(vector_test)

add_executable(shared_ptr_test shared_ptr_test.cpp)
target_link_libraries(shared_ptr_test gtest_main)
gtest_discover_tests(shared_ptr_test)

add_executable(memcpy_test memcpy_test.cpp)
target_link_libraries(memcpy_test gtest_main)
gtest_discover_tests(memcpy_test)
