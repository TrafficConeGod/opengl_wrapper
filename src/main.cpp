#include "glew/glew.hpp"
#include "gl/core.hpp"
#include "gl/shader_program.hpp"
#include "gl/io/read_file.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_attribute_array.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

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
        gl::io::read_file("shaders/vert.glsl"),
        gl::io::read_file("shaders/frag.glsl")
    );
    // auto texture = gl::io::load_texture<bmp_32_bpp_a8_r8_g8_b8>(program, "textures/test.bmp");
    // gl::uniform matrix_uniform(program, "mvp");
    // gl::uniform texture_uniform(program, "texture_sampler");

    std::vector<float> vertices = {
        //
        -1, -1,
        1, -1,
        -1, 1,
        //
        -1, 1,
        1, -1,
        1, 1
        //
    };

    gl::buffer vertex_pos_buffer;

    for (;;) {
        // Render
        gl::clear_frame({
            gl::enums::clear_frame_option::COLOR,
            gl::enums::clear_frame_option::DEPTH
        });

        program.use();

        {
            gl::vertex_attribute_array vertex_pos_array(0);
            vertex_pos_array.set_data<2, float>(vertex_pos_buffer, vertices);

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