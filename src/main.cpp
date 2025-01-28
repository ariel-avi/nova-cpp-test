#include <iostream>
#include <ostream>
#include <nodes.h>
#include <json_parser.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }


    json_parser parser{argv[1]};
    data_struct_t data = parser.read();
    data_struct_t final_result(data.size());
    for (size_t i{0}; i < data.size(); ++i) {
        data_node::ptr d_node = std::make_shared<data_node>(data[i]);
        rnd_node::ptr r_node = std::make_shared<rnd_node>(0x5702135);
        binary_node::ptr b_node = std::make_shared<binary_node>(d_node, r_node);
        max_node::ptr m_node = std::make_shared<max_node>(b_node);
        final_result[i].push_back(m_node->next());
    }
    std::cout << final_result;
    return 0;
}