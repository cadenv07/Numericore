//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_CAMERA_H
#define NUMERICORE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f):
        position(position),
        worldUp(up),
        yaw(yaw),
        pitch(pitch),
        camZoom(1.0f) {
        updateCameraVectors();
    };

    [[nodiscard]] glm::mat4 getViewMatrix() const { return glm::lookAt(position, position + front, up); };
    [[nodiscard]] glm::mat4 getProjectionMatrix(const float fov) const { return glm::perspective<float>(glm::radians(fov*camZoom), 16.0f / 9.0f, 0.001f, 10000.0f); };
    [[nodiscard]] glm::vec3 getPosition() const { return position; }
    [[nodiscard]] glm::vec3 getFront() const { return front; }
    [[nodiscard]] glm::vec3 getUp() const { return up; }
    [[nodiscard]] glm::vec3 getRight() const { return right; }
    [[nodiscard]] float getZoom() const { return camZoom; }
    [[nodiscard]] float getYaw() const { return yaw; }
    [[nodiscard]] float getPitch() const { return pitch; }

    void move(const glm::vec3& direction) { position += direction; }
    void moveForward(const float distance) { position += front * distance; }
    void moveRight(const float distance) { position += right * distance; }
    void moveUp(const float distance) { position += up * distance; }
    void rotate(const float xOffset, const float yOffset) { yaw += xOffset; pitch += yOffset; if (pitch > 89.0f) pitch = 89.0f; if (pitch < -89.0f) pitch = -89.0f; updateCameraVectors(); }
    void zoom(const float amount) { camZoom += amount; }
private:
    glm::vec3 position, front{}, up, right{};
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw,pitch,movementSpeed{},mouseSensitivity{},camZoom;
    void updateCameraVectors() {
        glm::vec3 tempFront;
        tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        tempFront.y = sin(glm::radians(pitch));
        tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(tempFront);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif //NUMERICORE_CAMERA_H