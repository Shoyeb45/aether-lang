#include <string>
#include <vector>

std::vector<std::string> read_file_contents(const std::string& filename);

std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);
std::string normalize_number_literal(const std::string &num);
std::string normalize_number_literal(const double num);
void verify_file_name(const std::string &file_name);