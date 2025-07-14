#ifndef VBO_HPP
#define VBO_HPP

#include "../lib/glad/glad.h"
#include <cstdio>

class VBO {
public:
  VBO(GLfloat vertices[], size_t size);
  void Bind();
  void BufferData(GLfloat vertices[], size_t size);
  void Unbind();
  void Delete();

private:
  GLuint vbo;
};

#endif /* VBO_HPP */
