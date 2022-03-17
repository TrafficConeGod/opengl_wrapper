#include "glew/glew.hpp"
#include "gl/core.hpp"
#include "gl/shader_program.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_attribute_array.hpp"
#include "gl/uniform.hpp"
#include "gl/texture.hpp"
#include "gl/io/io.hpp"
#include "std_ext/read_file.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <fmt/core.h>

int main() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if (win == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window");
    }
    glfwMakeContextCurrent(win);
    
    glew::set_experimental(true);
    glew::init();

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

    {
        using namespace gl;
        using namespace enums;
        enable(toggle::DEPTH_TEST);
        enable(toggle::CULL_FACE);
        enable(toggle::BLEND);

        set_depth_func(depth_func::LESS);
        set_blend_func(blend_func::SRC_ALPHA, blend_func::ONE_MINUS_SRC_ALPHA);

        set_clear_color(glm::vec3(44.f/256.f, 157.f/256.f, 222.f/256.f));

        gen_vertex_arrays(1);
    }

    gl::shader_program program(
        std::ext::read_file_as_string("shaders/vert.glsl"),
        std::ext::read_file_as_string("shaders/frag.glsl")
    );
    auto texture = gl::io::load_bmp(3, {
        .mag_filter = gl::enums::general::NEAREST,
        .min_filter = gl::enums::general::NEAREST
    }, std::ext::read_file_as_binary("textures/test.bmp"));

    glm::vec2 uv_shift_value(0.f, 0.f);
    gl::uniform<glm::vec2> uv_shift_uniform(program, "uv_shift_value");
    gl::uniform<gl::texture&> texture_uniform(program, "tex_sampler");
    texture_uniform.set(texture);

    auto vertices = {
        glm::vec2(1, 1),
        glm::vec2(-1, 1),
        glm::vec2(-1, -1),
        glm::vec2(1, -1)
    };

    auto uvs = {
        glm::vec2(1, 1),
        glm::vec2(0, 1),
        glm::vec2(0, 0),
        glm::vec2(1, 0)
    };

    std::initializer_list<gl::ubyte> indices = {
        0, 1, 2,
        0, 2, 3
    };

    gl::buffer<glm::vec2> vertex_pos_buf;
    vertex_pos_buf.set_data(vertices);

    gl::buffer<glm::vec2> vertex_uv_buf;
    vertex_uv_buf.set_data(uvs);

    program.use();

    for (;;) {
        // Render
        gl::clear_frame({
            gl::enums::clear_frame_option::COLOR,
            gl::enums::clear_frame_option::DEPTH
        });

        uv_shift_value.x += 0.005f;
        uv_shift_uniform.set(uv_shift_value);

        {
            gl::vertex_attribute_array<float> vertex_pos_array(0, 2, vertex_pos_buf);
            gl::vertex_attribute_array<float> vertex_uv_array(1, 2, vertex_uv_buf);
            gl::draw_elements<gl::ubyte>(gl::enums::draw_mode::TRIANGLES, indices);
        }

        glfwSwapBuffers(win);
	    glfwPollEvents();

        if (glfwWindowShouldClose(win)) {
            break;
        }
    }
    
    return 0;
}