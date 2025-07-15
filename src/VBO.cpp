#include "../include/VBO.hpp"

Vertex::Vertex(glm::vec3 pos, glm::vec3 color, glm::vec2 texUV,
               glm::vec3 normal) {
  Vertex::position = pos;
  Vertex::color = color;
  Vertex::texUV = texUV;
  Vertex::normal = normal;
};

VBO::VBO(std::vector<Vertex> vertices) {
  glGenBuffers(1, &vbo);
  Bind();
  BufferData(vertices);
}

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo); }

void VBO::BufferData(std::vector<Vertex> vertices) {
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
               vertices.data(), GL_STATIC_DRAW);
}

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Delete() { glDeleteBuffers(1, &vbo); }
