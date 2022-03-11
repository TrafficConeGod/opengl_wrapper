#include "glew/glew.hpp"
#include "gl/core.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

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
    }

    gl::gen_vertex_arrays();

    for (;;) {
        // Render
        gl::clear_frame({
            gl::enums::clear_frame_option::COLOR,
            gl::enums::clear_frame_option::DEPTH
        });

        glfwSwapBuffers(win);
	    glfwPollEvents();

        if (glfwWindowShouldClose(win)) {
            break;
        }
    }
    
    return 0;
}