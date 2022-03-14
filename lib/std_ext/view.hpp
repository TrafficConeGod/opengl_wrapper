#pragma once
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include "interpret_as.hpp"

namespace std::ext {
    template<typename T>
    class view {
        const T* data_;
        std::size_t size_;
        public:
            using const_pointer = const T*;
            using pointer = const T*;

            using const_iterator = __gnu_cxx::__normal_iterator<const T*, view>;

            inline view(const T* data_, std::size_t size_) : data_(data_), size_(size_) {}

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Winit-list-lifetime"
            template<typename C>
            inline view(const C& container) : data_(&(*container.begin())), size_(container.end() - container.begin()) {}
            #pragma GCC diagnostic pop

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Winit-list-lifetime"
            template<typename I>
            inline view(I begin, I end) : data_(&(*begin)), size_(end - begin) {}
            #pragma GCC diagnostic pop

            inline const T* data() const { return data_; }
            inline std::size_t size() const { return size_; }

            inline const T& operator[](std::size_t index) const { return data_[index]; }
            inline const T& at(std::size_t index) const {
                if (index >= size_) {
                    throw std::out_of_range("index out of range");
                }
                return data_[index];
            }

            inline const_iterator begin() const { return const_iterator(data_); }
            inline const_iterator end() const { return const_iterator(data_ + size_); }
    };
}