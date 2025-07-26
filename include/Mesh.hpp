#ifndef MESH_HPP
#define MESH_HPP

#include "Camera.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include <vector>

class Mesh {
public:
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
       std::vector<Texture> textures, GLuint shaderProgram);
  void SendTextureData(GLuint shaderProgram);
  void Draw(GLenum mode);
  void Delete();

private:
  VAO vao;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;
};

#endif /* MESH_HPP */
