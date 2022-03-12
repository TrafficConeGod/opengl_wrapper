#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <initializer_list>

namespace gl {
    template<typename T>
    class view {
        const T* data_;
        std::size_t size_;
        public:
            inline view(const T* data_, std::size_t size_) : data_(data_), size_(size_) {}
            inline view(const std::vector<T>& vec) : data_(vec.data()), size_(vec.size()) {}
            template<std::size_t N>
            inline view(const std::array<T, N>& arr) : data_(arr.data()), size_(N) {}
            inline view(std::initializer_list<T> list) : data_(list.begin()), size_(list.size()) {}

            inline const T* data() const { return data_; }
            inline std::size_t size() const { return size_; }
    };
}