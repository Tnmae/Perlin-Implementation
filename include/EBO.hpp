#ifndef EBO_HPP
#define EBO_HPP

#include "../lib/glad/glad.h"
#include <cstdio>
#include <vector>

class EBO {
public:
  EBO(std::vector<GLuint> indices);
  void Bind();
  void BufferData(std::vector<GLuint> indices);
  void Draw();
  void Unbind();
  void Delete();

private:
  GLuint ebo;
};

#endif /* EBO_HPP */
