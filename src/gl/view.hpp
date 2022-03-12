#pragma once
#include <cstdint>
#include <vector>
#include <stdexcept>

namespace gl {
    template<typename T>
    class view {
        const T* data_;
        std::size_t size_;
        public:
            using const_pointer = const T*;
            using pointer = const T*;

            using const_iterator = __gnu_cxx::__normal_iterator<const T*, view>;

            inline view(const T* data_, std::size_t size_) : data_(data_), size_(size_) {}

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

    template<typename T, typename C>
    inline view<T> make_view(const C& container) { return view<T>(container.data(), container.size()); }

    template<typename T, typename I>
    inline view<T> make_view(I begin, I end) { return view<T>(&(*begin), end - begin); }
}