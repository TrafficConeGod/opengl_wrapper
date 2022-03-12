#pragma once
#include <filesystem>
namespace fs = std::filesystem;
#include <string>
#include <fstream>

namespace gl::io {
    template<typename T = char>
    std::basic_string<T> read_file(const fs::path& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + path.string());
        }
        std::basic_stringstream<T> buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}