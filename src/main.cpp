#include <chrono>
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
#include "graphics/Light.h"
#include "graphics/Window.h"
#include "level/Level.h"
#include "util/InputHandler.h"

int main() {
    Window window(2560, 1440, "Numericore");

    Shader s("res/shaders/vert/shader.vert", "res/shaders/frag/shader.frag");

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    InputHandler input(window.getWindow());

    input.addKeyListener([&](const int key, int, const int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
    });

    input.addMouseMoveListener([&](double x, double y, const double dx, const double dy) {
       camera.rotate(static_cast<float>(dx)*0.08f,static_cast<float>(dy)*-0.08f);
    });

    input.addKeyListener([&](const int key, int, const int action, int) {
        if (key == GLFW_KEY_M && action == GLFW_PRESS)
            InputHandler::disableMouse(window.getWindow());
        if (key == GLFW_KEY_N && action == GLFW_PRESS)
            InputHandler::enableMouse(window.getWindow());
    });

    input.addScrollListener([&](const double x, const double y) {
        camera.zoom(static_cast<float>(y)*0.08f);
    });

    Light sl({ .direction = glm::vec3(0.f, 0.0f, -1.f), .ambient = glm::vec3(1.f),
        .diffuse = glm::vec3(.0f), .specular = glm::vec3(0.f)});

    Level level;

    using clock = std::chrono::steady_clock;
    auto lastFpsSample = clock::now();
    int frames = 0;

    while (!glfwWindowShouldClose(window.getWindow())) {
        // FPS counter (averaged over ~0.5s to avoid flicker)
        frames++;
        const auto now = clock::now();
        const std::chrono::duration<double> elapsed = now - lastFpsSample;
        if (elapsed.count() >= 0.5) {
            const double fps = static_cast<double>(frames) / elapsed.count();
            const std::string title = "Numericore - FPS: " + std::to_string(static_cast<int>(fps + 0.5));
            glfwSetWindowTitle(window.getWindow(), title.c_str());

            frames = 0;
            lastFpsSample = now;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input.beginFrame();

        if (input.isDownKey(GLFW_KEY_W))
            camera.moveForward(.1f);
        if (input.isDownKey(GLFW_KEY_A))
            camera.moveRight(-.1);
        if (input.isDownKey(GLFW_KEY_S))
            camera.moveForward(-.1);
        if (input.isDownKey(GLFW_KEY_D))
            camera.moveRight(.1);
        if (input.isDownKey(GLFW_KEY_LEFT_SHIFT))
            camera.moveUp(-.1);
        if (input.isDownKey(GLFW_KEY_SPACE))
            camera.moveUp(.1);

        s.setMat4("view", camera.getViewMatrix());
        s.setMat4("projection", camera.getProjectionMatrix(45));
        // s.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        s.setVec3("viewPos", camera.getPosition());

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        sl.apply(s);
        level.render(s);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // backpack.draw(s);
        // cube.draw(b);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    return 0;
}
