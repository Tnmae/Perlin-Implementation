#ifndef EBO_HPP
#define EBO_HPP

#include "../lib/glad/glad.h"
#include <cstdio>

class EBO {
public:
  EBO(GLuint indices[], size_t size);
  void Bind();
  void BufferData(GLuint indices[], size_t size);
  void Draw();
  void Unbind();
  void Delete();

private:
  GLuint ebo;
};

#endif /* EBO_HPP */
