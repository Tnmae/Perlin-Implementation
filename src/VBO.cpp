#include "../include/VBO.hpp"

VBO::VBO(GLfloat vertices[], size_t size) {
  glGenBuffers(1, &vbo);
  Bind();
  BufferData(vertices, size);
}

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, vbo); }

void VBO::BufferData(GLfloat vertices[], size_t size) {
  glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), vertices,
               GL_STATIC_DRAW);
}

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::Delete() { glDeleteBuffers(1, &vbo); }
