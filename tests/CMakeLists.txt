include(FetchContent)

FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(GTest)
include(GoogleTest)

add_executable(tests tests.cpp)

target_link_libraries(tests
        PRIVATE
        nova_lib
        GTest::gtest
        GTest::gtest_main
        PUBLIC
        data_resources
)
gtest_discover_tests(tests)
