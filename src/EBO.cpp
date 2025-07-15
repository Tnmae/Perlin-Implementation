#include "../include/EBO.hpp"

EBO::EBO(std::vector<GLuint> indices) {
  glGenBuffers(1, &ebo);
  Bind();
  BufferData(indices);
}

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); }

void EBO::BufferData(std::vector<GLuint> indices) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);
}

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete() { glDeleteBuffers(1, &ebo); }
