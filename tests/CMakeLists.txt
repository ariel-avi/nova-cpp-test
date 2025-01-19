include(FetchContent)

FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

FetchContent_MakeAvailable(GTest)

add_executable(tests test_read_json.cpp)

target_link_libraries(tests
        PRIVATE
        nova_lib
        GTest::gtest
        GTest::gtest_main
        PUBLIC
        data_resources
)

add_test(NAME Tests COMMAND tests)