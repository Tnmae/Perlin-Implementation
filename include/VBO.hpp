#ifndef VBO_HPP
#define VBO_HPP

#include "../lib/glad/glad.h"
#include <cstdio>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texUV;
  glm::vec3 normal;
  Vertex(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec2 texUV = glm::vec2(0.0f, 0.0f),
         glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f));
};

class VBO {
public:
  VBO(std::vector<Vertex> vertices);
  void Bind();
  void BufferData(std::vector<Vertex> vertices);
  void Unbind();
  void Delete();

private:
  GLuint vbo;
};

#endif /* VBO_HPP */
