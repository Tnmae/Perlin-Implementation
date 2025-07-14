#include "../include/Camera.hpp"
#include "../include/EBO.hpp"
#include "../include/VAO.hpp"
#include "../include/VBO.hpp"
#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include <GLFW/glfw3.h>

int main() {
  if (!glfwInit()) {
    std::cout << "error initializing GLFW " << std::endl;
    std::cout << glGetError() << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *gWindow =
      glfwCreateWindow(WIDTH, HEIGHT, "perlin implementation", NULL, NULL);

  glfwMakeContextCurrent(gWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "failed to initialize GLAD" << std::endl;
    return EXIT_FAILURE;
  }

  // gladLoadGL();

  GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 0.5f, 0.0f,
                        0.5f,  1.0f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

  GLuint indices[] = {0, 1, 2};

  glViewport(0, 0, WIDTH, HEIGHT);

  VAO VAO;
  VBO VBO(vertices, sizeof(vertices) / sizeof(GLfloat));
  EBO EBO(indices, sizeof(indices) / sizeof(GLuint));

  VAO.VertexArrayData(0, 3, 5, 0);
  VAO.VertexArrayData(1, 2, 5, 3);

  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();

  Texture sample("planks.png");

  Shader shader("default.vert", "default.frag");

  sample.TextureData(shader.shaderProgram, "texture", 0);

  while (!glfwWindowShouldClose(gWindow)) {
    glfwPollEvents();
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Activate();
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
    sample.DrawTexture(0);

    glfwSwapBuffers(gWindow);
  }

  glfwDestroyWindow(gWindow);
  VBO.Delete();
  VAO.Delete();
  EBO.Delete();
  shader.Delete();
  glfwTerminate();
  return EXIT_SUCCESS;
}
