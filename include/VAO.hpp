#ifndef VAO_HPP
#define VAO_HPP

#include "../lib/glad/glad.h"
#include "glm/glm.hpp"
#include <cstdio>

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
