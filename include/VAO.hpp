#ifndef VAO_HPP
#define VAO_HPP

#include "../lib/glad/glad.h"
#include "glm/glm.hpp"
#include <cstdio>

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

class VAO {
public:
  VAO();
  void Bind();
  void VertexArrayData(int count, int size, int stride, int data_begin_idx);
  void Unbind();
  void Delete();

private:
  GLuint vao;
};

#endif /*  VAO_HPP */
