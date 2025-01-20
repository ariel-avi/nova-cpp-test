#include <iostream>
#include <ostream>
#include <nodes.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }

    data_node::ptr d_node = std::make_shared<data_node>(argv[1]);
    auto data = d_node->execute();
    std::vector<int> r_node_data_size(data.size());
    for (int i = 0; i < data.size(); i++) {
        r_node_data_size[i] = data[i].size();
    }
    rnd_node::ptr r_node = std::make_shared<rnd_node>(r_node_data_size, 0x5702135);
    binary_node::ptr b_node = std::make_shared<binary_node>(d_node, r_node);
    max_node::ptr m_node = std::make_shared<max_node>(b_node);
    auto final_result = m_node->execute();
    std::cout << final_result;
    return 0;
}