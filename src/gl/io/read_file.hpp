#pragma once
#include <filesystem>
namespace fs = std::filesystem;
#include <string>

namespace gl::io {
    std::string read_file(const fs::path& path);
}