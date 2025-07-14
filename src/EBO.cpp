#include "../include/EBO.hpp"

EBO::EBO(GLuint indices[], size_t size) {
  glGenBuffers(1, &ebo);
  Bind();
  BufferData(indices, size);
}

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); }

void EBO::BufferData(GLuint indices[], size_t size) {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices,
               GL_STATIC_DRAW);
}

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void EBO::Delete() { glDeleteBuffers(1, &ebo); }
