#pragma once
#include "byte.hpp"
#include <filesystem>
namespace fs = std::filesystem;
#include <string>
#include <vector>

namespace std::ext {
    std::string read_file_as_string(const fs::path& path);
    std::vector<byte> read_file_as_binary(const fs::path& path);
}