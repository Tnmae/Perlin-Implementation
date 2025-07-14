#ifndef MESH_HPP
#define MESH_HPP

#include "Camera.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "shader.hpp"

class Mesh {
public:
  Mesh();

private:
  VAO vao;
};

#endif /* MESH_HPP */
