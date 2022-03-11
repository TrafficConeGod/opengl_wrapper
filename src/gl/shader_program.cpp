#include "shader_program.hpp"
using namespace gl;
#include <stdexcept>

template<GLuint type>
inline GLuint load_shader(std::string_view source) {
    GLuint id = glCreateShader(type);
    auto data = source.data();
    glShaderSource(id, 1, &data, nullptr);
    glCompileShader(id);

    // Check for errors
    GLint result = GL_NO_ERROR;
    int info_log_length;
    
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::string error_msg(info_log_length, ' ');
		glGetShaderInfoLog(id, info_log_length, NULL, error_msg.data());
		throw std::runtime_error(error_msg);
    }

    return id;
}

shader_program::shader_program(std::string_view vert_source, std::string_view frag_source) {
    auto vert_id = load_shader<GL_VERTEX_SHADER>(vert_source);
    auto frag_id = load_shader<GL_FRAGMENT_SHADER>(frag_source);

    // Link program
    id = glCreateProgram();
    glAttachShader(id, vert_id);
    glAttachShader(id, frag_id);
    glLinkProgram(id);

    // Check for errors
    GLint result = GL_NO_ERROR;
    int info_log_length;

    glGetProgramiv(id, GL_LINK_STATUS, &result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0) {
        std::string error_msg(info_log_length, ' ');
		glGetProgramInfoLog(id, info_log_length, NULL, error_msg.data());
		throw std::runtime_error(error_msg);
	}

    glDetachShader(id, vert_id);
    glDetachShader(id, frag_id);

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
}