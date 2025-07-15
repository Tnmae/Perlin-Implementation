#include "../include/Camera.hpp"
#include "../include/EBO.hpp"
#include "../include/Mesh.hpp"
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

  std::vector<Vertex> vertices = {
      Vertex(glm::vec3(-1.5f, -1.5f, 1.5f), glm::vec3(0.0f),
             glm::vec2(0.0f, 0.0f)),
      Vertex(glm::vec3(-1.5f, -1.5f, -1.5f), glm::vec3(0.0f),
             glm::vec2(1.0f, 0.0f)),
      Vertex(glm::vec3(1.5f, -1.5f, -1.5f), glm::vec3(0.0f),
             glm::vec2(0.0f, 1.0f)),
      Vertex(glm::vec3(1.5f, -1.5f, 1.5f), glm::vec3(0.0f),
             glm::vec2(1.0f, 0.0f)),
      Vertex{glm::vec3(-1.5f, 1.5f, 1.5f)},
      Vertex{glm::vec3(-1.5f, 1.5f, -1.5f)},
      Vertex{glm::vec3(1.5f, 1.5f, -1.5f)},
      Vertex{glm::vec3(1.5f, 1.5f, 1.5f)}};

  std::vector<GLuint> indices = {0, 1, 2, 0, 2, 3, 0, 4, 7, 0, 7, 3,
                                 3, 7, 6, 3, 6, 2, 2, 6, 5, 2, 5, 1,
                                 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7};

  std::vector<Texture> textures = {Texture("planks.png", "diffuse")};

  glViewport(0, 0, WIDTH, HEIGHT);

  Shader shader("default.vert", "default.frag");

  Mesh sample_mesh(vertices, indices, textures, shader.shaderProgram);

  Camera camera(glm::vec3(-1.0f, 3.0f, 11.0f));

  glm::vec3 mesh_pos = glm::vec3(0.0f, 0.0f, -2.0f);
  glm::mat4 model = glm::mat4(1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  float rotation = 0.5f;
  double prevTime = glfwGetTime();

  while (!glfwWindowShouldClose(gWindow)) {
    glfwPollEvents();
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double crntTime = glfwGetTime();
    if (crntTime - prevTime >= 1.0 / 60) {
      rotation += 0.5;
      prevTime = crntTime;
    }

    camera.HandleInputs(gWindow, 0.5f);
    camera.updateMatrix(0.1f, 100.0f);

    shader.Activate();
    camera.SendMatrix(shader.shaderProgram, "camera_matrix");
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1,
                       GL_FALSE, glm::value_ptr(model));
    sample_mesh.Draw();

    glfwSwapBuffers(gWindow);
  }

  glfwDestroyWindow(gWindow);
  shader.Delete();
  sample_mesh.Delete();
  glfwTerminate();
  return EXIT_SUCCESS;
}
