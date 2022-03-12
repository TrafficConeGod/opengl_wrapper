#pragma once
#include <GL/glew.h>

namespace gl {
    using enum_ = GLenum;
    using bit_field = GLbitfield;
    using uint = GLuint;
    using int_ = GLint;
    using size_t = GLsizei;
    using bool_ = GLboolean;
    using byte = GLbyte;
    using short_ = GLshort;
    using ubyte = GLubyte;
    using ushort_ = GLushort;
    using ulong = GLulong;
    using float_ = GLfloat;
    using clampf = GLclampf;
    using double_ = GLdouble;
    using clampd = GLclampd;
    using void_ = GLvoid;
    using int64_t = GLint64EXT;
    using uint64_t = GLuint64EXT;
    using sync = struct __GLsync *;

    using char_ = GLchar;
}