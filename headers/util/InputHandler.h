//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_INPUTHANDLER_H
#define NUMERICORE_INPUTHANDLER_H
#include <functional>
#include <vector>
#include <array>
#include <GLFW/glfw3.h>

class InputHandler {
public:
    using MouseMoveFn = std::function<void(double x, double y, double dx, double dy)>;
    using MouseBtnFn = std::function<void(int button, int action, int mods)>;
    using KeyFn = std::function<void(int key, int scancode, int action, int mods)>;
    using ScrollFn = std::function<void(double xOffset, double yOffset)>;
    using CharFn = std::function<void(unsigned int codepoint)>;

    explicit InputHandler(GLFWwindow* w) { attach(w); };
    InputHandler() = default;
    ~InputHandler() = default;

    void attach(GLFWwindow* w) {
        window = w;
        glfwSetWindowUserPointer(window, this);

        glfwSetCursorPosCallback(window, &InputHandler::glfwCursorPos);
        glfwSetMouseButtonCallback(window, &InputHandler::glfwMouseButton);
        glfwSetKeyCallback(window, &InputHandler::glfwKey);
        glfwSetScrollCallback(window, &InputHandler::glfwScroll);
        glfwSetCharCallback(window, &InputHandler::glfwChar);
    }

    void beginFrame() {
        lastKeys = keys; lastMouseButtons = mouseButtons;
        lastMouseX = mouseX; lastMouseY = mouseY;
        scrollX = scrollY = 0.0;
    }

    [[nodiscard]] bool isDownKey(const int key) const { return key >= 0 && key < keys.size() && keys[key];}
    [[nodiscard]] bool wasPressedKey(const int key) const { return isDownKey(key) && !lastKeys[key]; }
    [[nodiscard]] bool wasReleasedKey(const int key) const { return !isDownKey(key) && lastKeys[key]; }
    [[nodiscard]] bool isDownMouse(const int btn) const { return btn >= 0 && btn < mouseButtons.size() && mouseButtons[btn]; }
    [[nodiscard]] bool wasPressedMouse(const int btn) const { return isDownMouse(btn) && !lastMouseButtons[btn]; }
    [[nodiscard]] bool wasReleasedMouse(const int btn) const { return !isDownMouse(btn) && lastMouseButtons[btn]; }

    [[nodiscard]] double x() const { return mouseX; }
    [[nodiscard]] double y() const { return mouseY; }
    [[nodiscard]] double dx() const { return mouseX - lastMouseX; }
    [[nodiscard]] double dy() const { return mouseY - lastMouseY; }

    void addMouseMoveListener(const MouseMoveFn& fn) { mouseMoveListeners.push_back(fn); }
    void addMouseBtnListener(const MouseBtnFn& fn) { mouseBtnListeners.push_back(fn); }
    void addKeyListener(const KeyFn& fn) { keyListeners.push_back(fn); }
    void addScrollListener(const ScrollFn& fn) { scrollListeners.push_back(fn); }
    void addCharListener(const CharFn& fn) { charListeners.push_back(fn); }

    static void disableMouse(GLFWwindow* window) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    static void enableMouse(GLFWwindow* window) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

    void processInput(GLFWwindow* window);
    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
private:
    GLFWwindow* window = nullptr;

    std::array<bool, GLFW_KEY_LAST + 1> keys{};
    std::array<bool, GLFW_KEY_LAST + 1> lastKeys{};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> mouseButtons{};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> lastMouseButtons{};

    double mouseX = 0.0, mouseY = 0.0;
    double lastMouseX = 0.0, lastMouseY = 0.0;
    double scrollX = 0.0, scrollY = 0.0;

    std::vector<MouseMoveFn> mouseMoveListeners;
    std::vector<MouseBtnFn> mouseBtnListeners;
    std::vector<KeyFn> keyListeners;
    std::vector<ScrollFn> scrollListeners;
    std::vector<CharFn> charListeners;

    static InputHandler* self(GLFWwindow* w) {
        return static_cast<InputHandler*>(glfwGetWindowUserPointer(w));
    }

    static void glfwCursorPos(GLFWwindow* window, const double xPos, const double yPos) {
        if (auto* s = self(window)) s->onCursorPos(xPos, yPos);
    }
    static void glfwMouseButton(GLFWwindow* window, const int button, const int action, const int mods) {
        if (auto* s = self(window)) s->onMouseButton(button, action, mods);
    }
    static void glfwKey(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        if (auto* s = self(window)) s->onKey(key, scancode, action, mods);
    }
    static void glfwScroll(GLFWwindow* window, const double xOffset, const double yOffset) {
        if (auto* s = self(window)) s->onScroll(xOffset, yOffset);
    }
    static void glfwChar(GLFWwindow* window, const unsigned int codepoint) {
        if (const auto* s = self(window)) s->onChar(codepoint);
    }

    void onCursorPos(const double xPos, const double yPos) {
        mouseX = xPos; mouseY = yPos;
        const double ddx = mouseX - lastMouseX; const double ddy = mouseY - lastMouseY;
        for (auto& fn : mouseMoveListeners) fn(mouseX, mouseY, ddx, ddy);
    }
    void onMouseButton(const int button, const int action, const int mods) {
        if (button >= 0 && button < mouseButtons.size())
            mouseButtons[button] = (action != GLFW_RELEASE);
        for (auto& fn : mouseBtnListeners) fn(button, action, mods);
    }
    void onKey(const int key, const int scancode, const int action, const int mods) {
        if (key >= 0 && key < keys.size())
            keys[key] = (action != GLFW_RELEASE);
        for (auto& fn : keyListeners) fn(key, scancode, action, mods);
    }
    void onScroll(const double xOffset, const double yOffset) {
        scrollX += xOffset; scrollY += yOffset;
        for (auto& fn : scrollListeners) fn(xOffset, yOffset);
    }
    void onChar(const unsigned int codepoint) const {
        for (auto& fn : charListeners) fn(codepoint);
    }
};

#endif //NUMERICORE_INPUTHANDLER_H