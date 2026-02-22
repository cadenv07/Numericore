//
// Created by cadenv07 on 2/22/26.
//

#ifndef NUMERICORE_WINDOW_H
#define NUMERICORE_WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* getWindow() const { return window; }
private:
    GLFWwindow* window;
};


#endif //NUMERICORE_WINDOW_H