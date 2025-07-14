#include "../include/VAO.hpp"

Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 texUV,
               glm::vec3 normal) {
  Vertex::position = position;
  Vertex::color = color;
  Vertex::texUV = texUV;
  Vertex::normal = normal;
}

VAO::VAO() {
  glGenVertexArrays(1, &vao);
  Bind();
}

void VAO::Bind() { glBindVertexArray(vao); }

void VAO::VertexArrayData(int count, int size, int stride, int data_begin_idx) {
  glVertexAttribPointer(count, size, GL_FLOAT, GL_FALSE,
                        stride * sizeof(GLfloat),
                        (void *)(data_begin_idx * sizeof(GLfloat)));
  glEnableVertexAttribArray(count);
}

void VAO::Unbind() { glBindVertexArray(0); }

void VAO::Delete() { glDeleteVertexArrays(1, &vao); }
