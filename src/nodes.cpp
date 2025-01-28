#include "nodes.h"

#include <ostream>
#include <limits>

#include "json_parser.h"

binary_node::binary_node(ptr node_a, ptr node_b)
    : base_node(), a_(std::move(node_a)), b_(std::move(node_b))
{
}

bool binary_node::has_next() const
{
    return a_->has_next() && b_->has_next();
}

int binary_node::next()
{
    return a_->next() + b_->next();
}

max_node::max_node(ptr previous_node)
    : base_node(), previous_node_(std::move(previous_node))
{
}

bool max_node::has_next() const
{
    return previous_node_->has_next();
}

int max_node::next()
{
    int result = std::numeric_limits<int>::min();
    while (previous_node_->has_next()) {
        if (int next = previous_node_->next(); next > result) {
            result = next;
        }
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

rnd_node::rnd_node(size_t generator_seed_value)
    : base_node()
{
    generator_.seed(generator_seed_value);
}

int rnd_node::next()
{
    return distribution_(generator_);
}

bool rnd_node::has_next() const
{
    return true;
}

data_node::data_node(std::vector<int> data): data_(std::move(data)), iter_(data_.begin())
{
}

int data_node::next()
{
    if (iter_ == data_.end()) {
        throw std::runtime_error("Note iterator reached the end.");
    }
    int value = *iter_;
    ++iter_;
    return value;
}

bool data_node::has_next() const
{
    return iter_ != data_.end();
}