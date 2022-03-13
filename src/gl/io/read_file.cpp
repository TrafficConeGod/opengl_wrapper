#include "read_file.hpp"
using namespace gl;
#include <fstream>
#include <iterator>

std::string io::read_file_as_string(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path.string());
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<byte> io::read_file_as_binary(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    file.unsetf(std::ios::skipws);

    std::streampos file_size;

    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<byte> vec;
    vec.reserve(file_size);

    vec.insert(vec.begin(), std::istream_iterator<byte>(file), std::istream_iterator<byte>());

    return vec;
}