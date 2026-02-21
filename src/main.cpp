#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/models/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Camera.h"

int main() {
    std::printf("DISPLAY=%s\n", std::getenv("DISPLAY"));
    std::printf("XAUTHORITY=%s\n", std::getenv("XAUTHORITY"));

    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"Numericore", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW3" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
        return -1;
    }

    Texture t("res/textures/texture.jpg");
    const Shader s("res/shaders/vert/shader.vert", "res/shaders/frag/shader.frag");

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    Model backpack("res/models/backpack.obj");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s.use();
        glBindTexture(GL_TEXTURE_2D, t.getID());
        s.setMat4("view", camera.getViewMatrix());
        s.setMat4("projection", camera.getProjectionMatrix(45));
        backpack.draw(s);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}