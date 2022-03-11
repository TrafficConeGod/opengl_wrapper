#pragma once
#include <GL/glew.h>
#include <stdexcept>

namespace glew {
    inline void set_experimental(bool value) {
        glewExperimental = value;
    }
    inline void init() {
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }
    }
};