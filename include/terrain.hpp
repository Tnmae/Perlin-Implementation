#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../lib/glad/glad.h"
#include "Mesh.hpp"
#include "glm/glm.hpp"
#include "texture.hpp"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void *loadTerrainData(std::string file_name);

class Terrain {
public:
  Terrain(std::string file_name, GLuint shaderProgram);
  void RenderTerrain(GLenum mode);
  void Delete();

private:
  Mesh *terrain_mesh;
  unsigned char *data;
};

#endif /* TERRAIN_HPP */
