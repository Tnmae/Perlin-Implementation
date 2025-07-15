#include "../include/Camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/quaternion_geometric.hpp>

Camera::Camera(glm::vec3 camPos) { Camera::camPos = camPos; }

void Camera::updateMatrix(GLfloat nearPlane, GLfloat farPlane) {

  glm::mat4 camView = glm::mat4(1.0f);
  glm::mat4 camProj = glm::mat4(1.0f);

  camView = glm::lookAt(camPos, camPos + Orientation, Up);
  camProj = glm::perspective(
      glm::radians(45.0f), (float)(float(WIDTH) / HEIGHT), nearPlane, farPlane);

  camMatrix = camProj * camView;
}

void Camera::HandleInputs(GLFWwindow *window, GLfloat sensitivity) {
  GLfloat speed = 0.1f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camPos += speed * Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camPos += speed * -Orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camPos += speed * -glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camPos += speed * glm::normalize(glm::cross(Orientation, Up));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    camPos += speed * Up;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    camPos += speed * -Up;
  }

  // MOUSE EVENTS
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (firstClick) {
      glfwSetCursorPos(window, ((float)WIDTH / 2), ((float)HEIGHT / 2));
      firstClick = false;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    GLfloat rotX = sensitivity * (float)(mouseY - (float)(HEIGHT) / 2) / HEIGHT;
    GLfloat rotY = sensitivity * (float)(mouseX - (float)(WIDTH) / 2) / WIDTH;

    glm::vec3 newOrientation =
        glm::rotate(Orientation, glm::radians(-rotX),
                    glm::normalize(glm::cross(Orientation, Up)));
    if (fabs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <=
        glm::radians(85.0f)) {
      Orientation = newOrientation;
    }

    Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    glfwSetCursorPos(window, ((float)(WIDTH) / 2), ((float)(HEIGHT) / 2));

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
  }
}

void Camera::SendMatrix(GLuint shaderProgram, const char *uniform_name) {
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniform_name), 1,
                     GL_FALSE, glm::value_ptr(camMatrix));
}
