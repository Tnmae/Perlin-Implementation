#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "../lib/glad/glad.h"
#include "Mesh.hpp"
#include "base_utils.hpp"
#include "glm/glm.hpp"
#include "noise.hpp"
#include "texture.hpp"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <unistd.h>

namespace fs = std::filesystem;

void *loadTerrainData(std::string file_name);

namespace Filter {
void ApplyFIRSinglePoint(float *array2D, unsigned int terrain_size, int x,
                         int z, float &prevVal, double Filter);
void FIRFilter(float *array2D, int terrain_size, double Filter);
}; // namespace Filter

class Terrain {
public:
  float m_maxHeight;
  float m_minHeight;
  void InitTerrain(std::string file_name, GLuint shaderProgram,
                   float scalingFactor);
  void FaultFormationTechnique(unsigned int terrain_size,
                               unsigned int Iterations, float minHeight,
                               float maxHeight, float scalingFactor,
                               GLuint shaderProgram, double Filter);
  void MidpointDisplacementTechnique(unsigned int terrain_size,
                                     double roughness, float minHeight,
                                     float maxHeight, float scalingFactor,
                                     double Filter, GLuint shaderProgram);

  void FractalPerlinGeneration(unsigned int m_terrainSize, float minHeight,
                               float maxHeight, float scalingFactor,
                               unsigned int numOctaves, GLuint shaderProgram);

  void fBmUsingValueNoise(unsigned int m_terrainSize, float minHeight,
                          float maxHeight, float scalingFactor,
                          unsigned int numOctaves, GLuint shaderProgram);

  void ToggleWireframe(GLFWwindow *window);
  void RenderTerrain(GLenum mode);
  void Delete();
  int getTerrainSize() { return terrain_size; }
  void printArray2D();

private:
  Mesh *terrain_mesh;
  unsigned char *data;
  float m_worldScale = 1.0f;
  int terrain_size;
  float *array2D;
  GLenum mode = GL_LINE;
  bool firstClick = true;
};

#endif /* TERRAIN_HPP */
