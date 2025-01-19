# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest from its official repository
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # Use the latest stable version or specify a desired one
)

# Ensure the content is populated
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the test executable
add_executable(tests test_read_json.cpp)

# Link GoogleTest libraries to the test executable
target_link_libraries(tests
        PRIVATE
        nova_lib
        gtest
        gtest_main
        PUBLIC
        data_resources
)

# Add a test case to CTest
add_test(NAME Tests COMMAND tests)