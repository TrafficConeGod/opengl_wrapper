#pragma once
#include "enums/type.hpp"

namespace gl {
    template<typename T>
    struct get_type_enum {
        
    };

    template<>
    struct get_type_enum<gl::byte> {
        static constexpr enums::type value = enums::type::BYTE;
    };

    template<>
    struct get_type_enum<gl::ubyte> {
        static constexpr enums::type value = enums::type::UNSIGNED_BYTE;
    };

    template<>
    struct get_type_enum<gl::short_> {
        static constexpr enums::type value = enums::type::SHORT;
    };

    template<>
    struct get_type_enum<gl::ushort_> {
        static constexpr enums::type value = enums::type::UNSIGNED_SHORT;
    };

    template<>
    struct get_type_enum<gl::int_> {
        static constexpr enums::type value = enums::type::INT;
    };

    template<>
    struct get_type_enum<gl::uint> {
        static constexpr enums::type value = enums::type::UNSIGNED_INT;
    };

    template<>
    struct get_type_enum<gl::float_> {
        static constexpr enums::type value = enums::type::FLOAT;
    };

    template<>
    struct get_type_enum<gl::double_> {
        static constexpr enums::type value = enums::type::DOUBLE;
    };
}