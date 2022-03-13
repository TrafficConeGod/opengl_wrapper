#include "glew/glew.hpp"
#include "gl/core.hpp"
#include "gl/shader_program.hpp"
#include "gl/io/read_file.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_attribute_array.hpp"
#include "gl/uniform.hpp"
#include "gl/texture.hpp"
#include "gl/io/load_bmp.hpp"
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

        set_depth_func(general::LESS);
        set_blend_func(general::SRC_ALPHA, general::ONE_MINUS_SRC_ALPHA);

        set_clear_color(glm::vec3(44.f/256.f, 157.f/256.f, 222.f/256.f));

        gen_vertex_arrays(1);
    }

    gl::shader_program program(
        gl::io::read_file_as_string("shaders/vert.glsl"),
        gl::io::read_file_as_string("shaders/frag.glsl")
    );
    auto texture = gl::io::load_bmp(program, gl::make_view<gl::byte>(gl::io::read_file_as_binary("textures/test.bmp")));
    // gl::uniform matrix_uniform(program, "mvp");
    // gl::uniform texture_uniform(program, "texture_sampler");

    glm::vec2 color_shift_value(0.f, 0.f);
    gl::uniform<glm::vec2> color_shift_uniform(program, "color_shift_value");

    auto vertices = {
        //
        glm::vec2(-1, -1),
        glm::vec2(1, -1),
        glm::vec2(-1, 1),
        //
        glm::vec2(-1, 1),
        glm::vec2(1, -1),
        glm::vec2(1, 1)
        //
    };

    auto uvs = {
        //
        glm::vec2(0, 0),
        glm::vec2(1, 0),
        glm::vec2(0, 1),
        //
        glm::vec2(0, 1),
        glm::vec2(1, 0),
        glm::vec2(1, 1)
        //
    };

    gl::buffer<glm::vec2> vertex_pos_buf;
    vertex_pos_buf.set_data(gl::make_view<glm::vec2>(vertices.begin(), vertices.end()));

    gl::buffer<glm::vec2> vertex_uv_buf;
    vertex_uv_buf.set_data(gl::make_view<glm::vec2>(uvs.begin(), uvs.end()));

    program.use();

    for (;;) {
        // Render
        gl::clear_frame({
            gl::enums::clear_frame_option::COLOR,
            gl::enums::clear_frame_option::DEPTH
        });

        color_shift_value.x += 0.005f;
        color_shift_uniform.set(color_shift_value);

        {
            gl::vertex_attribute_array<float> vertex_pos_array(0, 2, vertex_pos_buf);
            gl::vertex_attribute_array<float> vertex_uv_array(1, 2, vertex_uv_buf);
            gl::draw_attribute_arrays(gl::enums::general::TRIANGLES, vertices.size());
        }

        glfwSwapBuffers(win);
	    glfwPollEvents();

        if (glfwWindowShouldClose(win)) {
            break;
        }
    }
    
    return 0;
}