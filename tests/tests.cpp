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

    data_node::ptr a_node = std::make_shared<data_node>(a);
    data_node::ptr b_node = std::make_shared<data_node>(b);
    binary_node::ptr result_node_ptr = std::make_shared<binary_node>(a_node, b_node);
    std::vector<int> result;
    while (result_node_ptr->has_next()) {
        result.push_back(result_node_ptr->next());
        EXPECT_EQ(result.back(), 11);
    }
    ASSERT_EQ(result.size(), a.size());
}

struct max_node_test_inputs {
    std::vector<int> inputs;
    int expected_result;

    max_node_test_inputs(std::vector<int> vector, int i) : inputs(std::move(vector)),
                                                           expected_result(i)
    {
    }
};

class max_node_test_fixture : public ::testing::Test,
                              public ::testing::WithParamInterface<max_node_test_inputs> {
};

TEST_P(max_node_test_fixture, find_max)
{
    data_node::ptr d_node = std::make_shared<data_node>(GetParam().inputs);
    max_node::ptr m_node = std::make_shared<max_node>(d_node);
    EXPECT_EQ(m_node->next(), GetParam().expected_result);
    ASSERT_FALSE(m_node->has_next());
}

INSTANTIATE_TEST_SUITE_P(values,
                         max_node_test_fixture,
                         ::testing::Values(
                             max_node_test_inputs(std::vector{1, 2, 3, 10, 2, 3},10),
                             max_node_test_inputs(std::vector{1, 2, 3, 1, 20, 3},20),
                             max_node_test_inputs(std::vector{1, 2, 3, 10, 20, 30},30),
                             max_node_test_inputs(std::vector{1, 2, 40, 10, 20, 30},40),
                             max_node_test_inputs(std::vector{1, 2, 40, 50, 20, 30},50)
                         )
    );

TEST(node_chain, execute)
{
    json_parser parser{DATA_FILE};
    data_struct_t data = parser.read();
    data_struct_t final_result(data.size());
    for (size_t i{0}; i < data.size(); ++i) {
        data_node::ptr d_node = std::make_shared<data_node>(data[i]);
        rnd_node::ptr r_node = std::make_shared<rnd_node>(0x5702135);
        binary_node::ptr b_node = std::make_shared<binary_node>(d_node, r_node);
        max_node::ptr m_node = std::make_shared<max_node>(b_node);
        final_result[i].push_back(m_node->next());
        ASSERT_FALSE(m_node->has_next());
    }
    ASSERT_EQ(final_result.size(), 11);
}