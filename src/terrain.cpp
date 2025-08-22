#include "../include/terrain.hpp"
#include <glm/integer.hpp>
#include <thread>

void *loadTerrainData(std::string file_name, size_t &out_size) {
  std::string current_path = fs::current_path().string();

  std::string path = current_path + "/../resources/textures/" + file_name;
  std::cout << "Loading height map from location : " << path << std::endl;
  std::ifstream file(path, std::ios::binary);

  if (!file) {
    std::cerr << "error loading height map" << std::endl;
    out_size = 0;
    return nullptr;
  }

  file.seekg(0, std::ios::end);
  size_t size = file.tellg();
  file.seekg(0, std::ios::beg);

  char *p = (char *)malloc(size);
  if (!p) {
    std::cerr << "data allocation failed" << std::endl;
    out_size = 0;
    return nullptr;
  }

  file.read(p, size);
  if (!file) {
    std::cerr << "failed to read the contents of the file" << std::endl;
    out_size = 0;
    free(p);
    return nullptr;
  }

  out_size = size;
  return p;
}

void Filter::ApplyFIRSinglePoint(float *array2D, unsigned int terrain_size,
                                 int x, int z, float &prevVal, double Filter) {
  int curIdx = z * terrain_size + x;
  *(array2D + curIdx) = prevVal * Filter + (1.0 - Filter) * *(array2D + curIdx);
  prevVal = *(array2D + curIdx);
}

void Filter::FIRFilter(float *array2D, int terrain_size, double Filter) {
  // left to right
  for (int i = 0; i < terrain_size; i++) {
    float prevVal = *(array2D + i * terrain_size);
    for (int j = 1; j < terrain_size; j++) {
      Filter::ApplyFIRSinglePoint(array2D, terrain_size, j, i, prevVal, Filter);
    }
  }

  // right to left
  for (int i = 0; i < terrain_size; i++) {
    float prevVal = *(array2D + i * terrain_size + terrain_size - 1);
    for (int j = terrain_size - 2; j >= 0; j--) {
      Filter::ApplyFIRSinglePoint(array2D, terrain_size, j, i, prevVal, Filter);
    }
  }

  // top to bottom
  for (int j = 0; j < terrain_size; j++) {
    float prevVal = *(array2D + j);
    for (int i = 1; i < terrain_size; i++) {
      Filter::ApplyFIRSinglePoint(array2D, terrain_size, j, i, prevVal, Filter);
    }
  }

  // bottom to top
  for (int j = 0; j < terrain_size; j++) {
    float prevVal = *(array2D + (terrain_size - 1) * terrain_size + j);
    for (int i = terrain_size - 2; i >= 0; i--) {
      Filter::ApplyFIRSinglePoint(array2D, terrain_size, j, i, prevVal, Filter);
    }
  }
}

void Terrain::InitTerrain(std::string file_name, GLuint shaderProgram,
                          float scalingFactor) {
  Terrain::m_worldScale = scalingFactor;

  size_t size;
  float *data = (float *)loadTerrainData(file_name, size);
  int terrain_size = std::sqrt((float)size / sizeof(float));

  Terrain::terrain_size = terrain_size;

  Terrain::array2D =
      (float *)malloc(terrain_size * terrain_size * sizeof(float));

  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      *(array2D + i * terrain_size + j) = *(data + i * terrain_size + j);
    }
  }

  free(data);

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  Utility::PopulateBuffers(Terrain::array2D, vertices, indices,
                           Terrain::terrain_size, m_worldScale);

  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::FaultFormationTechnique(unsigned int terrain_size,
                                      unsigned int Iteration, float minHeight,
                                      float maxHeight, float scalingFactor,
                                      GLuint shaderProgram, double Filter) {
  Terrain::terrain_size = terrain_size;
  Terrain::m_worldScale = scalingFactor;
  Terrain::m_maxHeight = maxHeight;
  Terrain::m_minHeight = minHeight;

  float delta_height = maxHeight - minHeight;

  Terrain::array2D =
      (float *)malloc(terrain_size * terrain_size * sizeof(float));

  Utility::initArray2D(Terrain::array2D, terrain_size);

  for (int cur_iter = 0; cur_iter < Iteration; cur_iter++) {
    float iteration_ratio = ((float)cur_iter / (float)Iteration);
    float height = maxHeight - iteration_ratio * delta_height;

    int randX1 = rand() % terrain_size;
    int randZ1 = rand() % terrain_size;

    int counter = 0;

    int randX2, randZ2;

    do {
      randX2 = rand() % terrain_size;
      randZ2 = rand() % terrain_size;

      if (counter++ == 1000) {
        std::cout << "endless loop detected" << __FILE__ << __LINE__
                  << std::endl;
        assert(0);
      }
    } while (randX1 == randX2 && randZ1 == randZ2);

    int dirX = randX2 - randX1;
    int dirZ = randZ2 - randZ1;

    for (int i = 0; i < terrain_size; i++) {
      int dirZ_in = i - randZ1;
      for (int j = 0; j < terrain_size; j++) {
        int dirX_in = j - randX1;

        int cross_product = dirX_in * dirZ - dirX * dirZ_in;

        if (cross_product > 0) {
          *(Terrain::array2D + i * terrain_size + j) += height;
        }
      }
    }
  }

  float min, max;
  Utility::getMinMaxValue(Terrain::array2D, terrain_size, min, max);

  Utility::Normalize(Terrain::array2D, terrain_size, min, max, minHeight,
                     maxHeight);

  Filter::FIRFilter(Terrain::array2D, terrain_size, Filter);

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  Utility::PopulateBuffers(Terrain::array2D, vertices, indices,
                           Terrain::terrain_size, Terrain::m_worldScale);

  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::MidpointDisplacementTechnique(unsigned int terrain_size,
                                            double roughness, float minHeight,
                                            float maxHeight,
                                            float scalingFactor, double Filter,
                                            GLuint shaderProgram) {
  Terrain::terrain_size = terrain_size;
  Terrain::m_maxHeight = maxHeight;
  Terrain::m_minHeight = minHeight;
  Terrain::m_worldScale = scalingFactor;

  int m_rectSize = terrain_size;
  float m_heightReduce = std::pow(2.0f, -roughness);
  int curHeight = (float)m_rectSize / 2.0f;

  Terrain::array2D =
      (float *)malloc(terrain_size * terrain_size * sizeof(float));

  Utility::initArray2D(Terrain::array2D, terrain_size);

  while (m_rectSize > 0) {

    Utility::diamondStep(Terrain::array2D, terrain_size, m_rectSize, curHeight);

    Utility::squareStep(Terrain::array2D, terrain_size, m_rectSize, curHeight);

    m_rectSize >>= 1;
    curHeight *= m_heightReduce;
  }

  float min, max;
  Utility::getMinMaxValue(Terrain::array2D, terrain_size, min, max);

  Utility::Normalize(Terrain::array2D, terrain_size, min, max, minHeight,
                     maxHeight);

  Filter::FIRFilter(Terrain::array2D, terrain_size, Filter);

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  Utility::PopulateBuffers(Terrain::array2D, vertices, indices, terrain_size,
                           Terrain::m_worldScale);

  terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::FractalPerlinGeneration(unsigned int m_terrainSize,
                                      float minHeight, float maxHeight,
                                      float scalingFactor,
                                      unsigned int numOctaves,
                                      GLuint shaderProgram) {
  Terrain::terrain_size = m_terrainSize;
  Terrain::m_minHeight = minHeight;
  Terrain::m_maxHeight = maxHeight;
  Terrain::m_worldScale = scalingFactor;

  makePermutation();

  Terrain::array2D =
      (float *)malloc(m_terrainSize * m_terrainSize * sizeof(float));

  Utility::initArray2D(Terrain::array2D, m_terrainSize);

  float delta_height = maxHeight - minHeight;

  int curOctave = 0;
  double amplitude = 1.0f;
  double frequency = 0.005f;

  while (curOctave < numOctaves) {
    for (int i = 0; i < m_terrainSize; i++) {
      float x = i * frequency;
      for (int j = 0; j < m_terrainSize; j++) {
        float y = j * frequency;
        *(array2D + i * m_terrainSize + j) +=
            delta_height * amplitude * ((float)(1.0f + Noise2D(x, y)) / 2.0f) +
            minHeight;
      }
    }
    amplitude *= 0.5f;
    frequency *= 2.0f;
    curOctave++;
  }

  float min, max;

  Utility::getMinMaxValue(Terrain::array2D, terrain_size, min, max);

  Utility::Normalize(Terrain::array2D, m_terrainSize, min, max, minHeight,
                     maxHeight);

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  Utility::PopulateBuffers(Terrain::array2D, vertices, indices, terrain_size,
                           Terrain::m_worldScale);

  Terrain::terrain_mesh = new Mesh(vertices, indices, {}, shaderProgram);
}

void Terrain::Delete() { terrain_mesh->Delete(); }

void Terrain::RenderTerrain(GLenum mode) {
  glPolygonMode(GL_FRONT_AND_BACK, Terrain::mode);
  terrain_mesh->Draw(mode);
}

void Terrain::ToggleWireframe(GLFWwindow *window) {
  static bool qWasPressed = false;

  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    if (!qWasPressed) { // key just pressed
      Terrain::firstClick = !Terrain::firstClick;
      Terrain::mode = Terrain::firstClick ? GL_FILL : GL_LINE;
    }
    qWasPressed = true;
  } else {
    qWasPressed = false; // key released
  }
}

void Terrain::printArray2D() {
  float *ptr = array2D;
  for (int i = 0; i < terrain_size; i++) {
    for (int j = 0; j < terrain_size; j++) {
      std::cout << *ptr << " ";
      ptr++;
    }
    std::cout << "\n";
  }
}
