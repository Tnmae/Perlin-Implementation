#include "../include/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
           std::vector<Texture> textures, GLuint shaderProgram) {
  Mesh::indices = indices;
  Mesh::textures = textures;

  vao.Bind();

  VBO vbo(vertices);
  EBO ebo(indices);

  vao.VertexArrayData(0, 3, 11, 0);
  vao.VertexArrayData(1, 3, 11, 3);
  vao.VertexArrayData(2, 2, 11, 6);
  vao.VertexArrayData(3, 8, 11, 8);

  vao.Unbind();

  SendTextureData(shaderProgram);
}

void Mesh::SendTextureData(GLuint shaderProgram) {
  glUseProgram(shaderProgram);

  unsigned int num_diff = 0;
  unsigned int num_spec = 0;
  unsigned int num_norm = 0;
  unsigned int num_height = 0;

  std::string uniform_name;

  for (int i = 0; i < textures.size(); i++) {
    if (textures[i].type == "diffuse") {
      uniform_name = "diffuse" + std::to_string(num_diff);
      num_diff++;
    } else if (textures[i].type == "specular") {
      uniform_name = "specular" + std::to_string(num_spec);
      num_spec++;
    } else if (textures[i].type == "normal") {
      uniform_name = "normal" + std::to_string(num_norm);
      num_norm++;
    } else if (textures[i].type == "height") {
      uniform_name = "height" + std::to_string(num_height);
      num_height++;
    } else {
      std::cout << "undefined texture type..." << std::endl;
    }
    std::cout << uniform_name << std::endl;
    textures[i].TextureData(shaderProgram, uniform_name, i);
  }
}

void Mesh::Draw() {
  vao.Bind();

  for (int i = 0; i < textures.size(); i++) {
    textures[i].DrawTexture(i);
  }

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Delete() { vao.Delete(); }
