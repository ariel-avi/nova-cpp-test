
#include "json_parser.h"
#include <fstream>
#include <iostream>

json_parser::json_parser(const std::string& file_path) : file_path_(file_path) {}

std::vector<int> json_parser::read_row(const std::string& raw_string)
{
    std::vector<int> vector;
    std::size_t inner_beg_pos = 0UL;
    while (inner_beg_pos != std::string::npos) {
        const auto inner_end_pos = raw_string.find(',', inner_beg_pos + 1);
        auto int_str = raw_string.substr(inner_beg_pos, inner_end_pos - inner_beg_pos);
        std::cout << int_str << ' ';
        if (int_str.empty()) {
            throw std::runtime_error("json_parser::read: empty string");
        }
        vector.emplace_back(std::stoi(int_str));
        if (inner_end_pos == std::string::npos) {
            break;
        }
        inner_beg_pos = inner_end_pos + 1;
    }
    return vector;
}

json_parser::data_t json_parser::read() const
{
    data_t result;
    std::ifstream file(file_path_, std::ios::in | std::ios::ate);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string contents(file_size, '\0');
    file.read(&contents[0], file_size);
    file.close();

    auto pos = contents.find('[', 0);
    while (true) {
        if (const auto beg_pos = contents.find('[', pos + 1);
            beg_pos != std::string::npos) {
            if (const auto end_pos = contents.find(']', beg_pos + 1);
                end_pos != std::string::npos) {
                auto int_contents = contents.substr(beg_pos + 1, end_pos - beg_pos - 1);
                result.emplace_back(read_row(int_contents));
                pos =  end_pos;
                if (contents.find(',', pos) == std::string::npos) {
                    break;
                }
            } else {
                throw std::runtime_error("json_parser::read() file parse error");
            }
        }
    }

    if (const auto end_pos = contents.find(']', pos + 1);
        end_pos == std::string::npos) {
        throw std::runtime_error("json_parser::read(): invalid end char");
    } else {
        pos = end_pos;
    }

    return result;
}
