#include <gtest/gtest.h>
#include <json_parser.h>

#ifndef DATA_FILE
#error "DATA_FILE not defined"
#endif

TEST(JsonParser, read_file_into_vectors) {
    json_parser parser(DATA_FILE);
    auto data = parser.read();
    ASSERT_EQ(data.size(), 11);
    EXPECT_EQ(data[0].size(), 1);
    EXPECT_EQ(data[1].size(), 4);
    EXPECT_EQ(data[2].size(), 8);
    EXPECT_EQ(data[8].size(), 1);
    EXPECT_EQ(data[9].size(), 8);
    EXPECT_EQ(data[0].front(), 9);
    EXPECT_EQ(data[1].front(), 5);
    EXPECT_EQ(data[1].back(), -7);
    EXPECT_EQ(data[2].front(), -8);
    EXPECT_EQ(data[2].back(), 7);
    EXPECT_EQ(data[10].front(), 43);
    EXPECT_EQ(data[10].back(), 97);
}
