#ifndef NODES_H
#define NODES_H

#include <memory>
#include <vector>
#include <string>
#include <random>

template <typename T>
class iterator_t {

};

template <class T> class base_node {
public:
    base_node() = default;

    virtual ~base_node() = default;

    [[nodiscard]] virtual bool has_next() const = 0;

    virtual T next() = 0;

    typedef std::shared_ptr<base_node<T> > ptr;
};

typedef std::vector<std::vector<int> > data_struct_t;

std::ostream& operator<<(std::ostream& os, const data_struct_t& data);

std::ostream& operator<<(std::ostream& os, const std::vector<int>& data);

class rnd_node : public base_node<int> {
public:
    explicit rnd_node(size_t generator_seed_value);

    [[nodiscard]] bool has_next() const override;

    int next() override;

private:
    std::uniform_int_distribution<> distribution_;
    std::mt19937 generator_;
};

class data_node : public base_node<int> {
public:
    explicit data_node(std::vector<int> data);

    [[nodiscard]] bool has_next() const override;

    int next() override;

private:
    std::vector<int> data_;
    std::vector<int>::iterator iter_;
};

class binary_node : public base_node<int> {

public:
    binary_node(ptr node_a, ptr node_b);

    [[nodiscard]] bool has_next() const override;

    int next() override;

private:
    ptr a_;
    ptr b_;
};

class max_node : public base_node<int> {
public:
    explicit max_node(ptr previous_node);

    [[nodiscard]] bool has_next() const override;

    int next() override;

private:
    ptr previous_node_;
};

#endif //NODES_H