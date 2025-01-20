#ifndef DATA_FILE
#error "DATA_FILE not defined"
#endif

#include <gtest/gtest.h>
#include <json_parser.h>
#include <nodes.h>

TEST(json_parser, read_file_into_vectors)
{
    const json_parser parser(DATA_FILE);
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
    ASSERT_TRUE(std::find(data[10].begin(), data[10].end(), 2147483647) != data[10].end());
}

TEST(binary_node, sum_vectors)
{
    const std::vector a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const std::vector b = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    const std::vector<int> c = a + b;
    ASSERT_EQ(c.size(), a.size());
    for (int i : c) {
        EXPECT_EQ(i, 11);
    }
}

class constant_node : public base_node<data_struct_t> {
public:
    explicit constant_node() = default;

    data_struct_t execute() override
    {
        return {
            std::vector{1, 2, 3, 10, 2, 3},
            std::vector{1, 2, 3, 1, 20, 3},
            std::vector{1, 2, 3, 10, 20, 30},
            std::vector{1, 2, 40, 10, 20, 30},
            std::vector{1, 2, 40, 50, 20, 30},
        };
    }
};

TEST(max_node, execute)
{
    constant_node::ptr c_node = std::make_shared<constant_node>();
    max_node::ptr m_node = std::make_shared<max_node>(c_node);
    auto result = m_node->execute();
    ASSERT_EQ(result.size(), 5);
    EXPECT_EQ(result[0].front(), 10);
    EXPECT_EQ(result[1].front(), 20);
    EXPECT_EQ(result[2].front(), 30);
    EXPECT_EQ(result[3].front(), 40);
    EXPECT_EQ(result[4].front(), 50);
}

TEST(node_chain, execute)
{
    data_node::ptr d_node = std::make_shared<data_node>(DATA_FILE);
    auto data = d_node->execute();
    std::vector<int> r_node_data_size(data.size());
    for (int i = 0; i < data.size(); i++) {
        r_node_data_size[i] = data[i].size();
    }
    rnd_node::ptr r_node = std::make_shared<rnd_node>(r_node_data_size, 0x5702135);
    binary_node::ptr b_node = std::make_shared<binary_node>(d_node, r_node);
    max_node::ptr m_node = std::make_shared<max_node>(b_node);
    auto final_result = m_node->execute();
    ASSERT_EQ(final_result.size(), 11);
}