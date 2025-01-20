#include "nodes.h"

#include <ostream>

#include "json_parser.h"


std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size()) {
        throw std::invalid_argument("Binary operation does not support the same size");
    }
    std::vector<int> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] + b[i];
    }
    return result;
}

binary_node::binary_node(ptr node_a, ptr node_b)
    : base_node(), a_(std::move(node_a)), b_(std::move(node_b))
{
}

data_struct_t binary_node::execute()
{
    const data_struct_t result_a{a_->execute()};
    const data_struct_t result_b{b_->execute()};
    if (result_a.size() != result_b.size()) {
        throw std::runtime_error("Binary operation does not support the same size");
    }
    data_struct_t result;
    for (int i = 0; i < result_a.size(); i++) {
        result.push_back(result_a[i] + result_b[i]);
    }
    return result;
}

max_node::max_node(ptr previous_node)
    : base_node(), previous_node_(std::move(previous_node))
{
}

data_struct_t max_node::execute()
{
    const data_struct_t previous_result{previous_node_->execute()};
    data_struct_t result;
    for (auto& v : previous_result) {
        result.push_back(std::vector{{*std::max_element(v.begin(), v.end())}});
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const data_struct_t& data)
{
    for (auto& v : data) {
        os << v << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data)
{
    auto it = data.begin();
    while (it != data.end()) {
        os << *it;
        if (++it != data.end()) {
            os << ' ';
        }
    }
    return os;
}

rnd_node::rnd_node(const std::vector<int>& data_size, size_t generator_seed_value)
    : base_node(), data_size_(data_size)
{
    generator_.seed(generator_seed_value);
}

data_struct_t rnd_node::execute()
{
    data_struct_t result(data_size_.size(), std::vector<int>{});
    for (size_t i = 0; i < data_size_.size(); i++) {
        std::vector<int> row(data_size_[i]);
        for (size_t j = 0; j < data_size_[i]; j++) {
            row[i] = distribution_(generator_);
        }
        result[i] = std::move(row);
    }
    return result;
}

data_node::data_node(std::string file_path): file_path_(std::move(file_path))
{
}

std::vector<std::vector<int> > data_node::execute()
{
    json_parser parser{file_path_};
    return parser.read();
}