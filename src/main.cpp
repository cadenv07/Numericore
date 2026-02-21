#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"
#include "graphics/Texture.h"

float vertices[] = {
    .5f, .5f, .0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    .5f, -.5f, .0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -.5f, -.5f, .0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -.5f, .5f, .0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

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

    const Shader s("res/shaders/vert/shader.vert", "res/shaders/frag/shader.frag");
    s.use();

    const Texture t("res/textures/texture.jpg");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(s.getID());
        glBindTexture(GL_TEXTURE_2D, t.getID());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}