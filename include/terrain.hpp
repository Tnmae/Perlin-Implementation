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

namespace Filter {
void FIRFilter(float *array2D, int terrain_size, double Filter);
};

class Terrain {
public:
  void InitTerrain(std::string file_name, GLuint shaderProgram,
                   float scalingFactor);
  void FaultFormationTechnique(int terrain_size, int Iterations,
                               float minHeight, float maxHeight,
                               float scalingFactor, GLuint shaderProgram,
                               double Filter);
  void MidpointDisplacementTechnique(int terrain_size);
  float m_maxHeight;
  float m_minHeight;
  void RenderTerrain(GLenum mode, bool wireframe = false);
  void Delete();
  int getTerrainSize() { return terrain_size; }
  void printArray2D();

private:
  Mesh *terrain_mesh;
  unsigned char *data;
  float m_worldScale = 1.0f;
  int terrain_size;
  float *array2D;
};

#endif /* TERRAIN_HPP */
