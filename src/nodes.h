#ifndef NODES_H
#define NODES_H

#include <memory>
#include <vector>
#include <string>
#include <random>

template <class T> class base_node {
public:
    base_node() = default;

    virtual ~base_node() = default;

    [[nodiscard]] virtual T execute() = 0;

    typedef std::shared_ptr<base_node<T> > ptr;
};

typedef std::vector<std::vector<int> > data_struct_t;

std::ostream& operator<<(std::ostream& os, const data_struct_t& data);

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data);

class rnd_node : public base_node<data_struct_t> {
public:
    explicit rnd_node(const std::vector<int>& data_size, size_t generator_seed_value);

    data_struct_t execute() override;

private:
    std::uniform_int_distribution<> distribution_;
    std::mt19937 generator_;
    std::vector<int> data_size_;
};

class data_node : public base_node<data_struct_t> {
public:
    explicit data_node(std::string file_path);

    [[nodiscard]] data_struct_t execute() override;

private:
    std::string file_path_;
};

std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b);

class binary_node : public base_node<data_struct_t> {
public:
    binary_node(ptr node_a, ptr node_b);

    [[nodiscard]] data_struct_t execute() override;

private:
    ptr a_;
    ptr b_;
};

class max_node : public base_node<data_struct_t> {
public:
    explicit max_node(ptr previous_node);

    [[nodiscard]] data_struct_t execute() override;

private:
    ptr previous_node_;
};

#endif //NODES_H