#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <vector>

class json_parser {
  public:
    using data_t = std::vector<std::vector<int>>;
    explicit json_parser(const std::string& file_path);
    [[nodiscard]] data_t read() const;

  private:
    static std::vector<int> read_row(const std::string& raw_string);
    std::string file_path_;
};

#endif // JSON_PARSER_H
