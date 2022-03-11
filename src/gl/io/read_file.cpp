#include "read_file.hpp"
using namespace gl::io;
#include <fstream>
#include <stdexcept>

std::string gl::io::read_file(const fs::path& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + path.string());
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}