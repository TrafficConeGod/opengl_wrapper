#pragma once
#include <stdexcept>

namespace std::ext {
    template<typename T, typename I>
    T interpret_as(I begin, I container_end) {
        if (begin + sizeof(T) >= container_end) {
            throw std::runtime_error("invalid data size");
        }
        return *reinterpret_cast<const T*>(&(*begin));
    }
}