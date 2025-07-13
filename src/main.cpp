#include "thirdParty/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#define W_WIDTH 1080
#define W_HEIGHT 720

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.0);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3.0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *gWindow =
      glfwCreateWindow(W_WIDTH, W_HEIGHT, "terrain", NULL, NULL);

  gladLoadGL();

  glfwDestroyWindow(gWindow);
  glfwTerminate();

  return EXIT_SUCCESS;
}
