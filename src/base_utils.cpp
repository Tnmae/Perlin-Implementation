#include "../include/base_utils.hpp"

#define RANDOM_FLOAT ((float)rand() / (float)RAND_MAX)

float RandomFloatRange(int min, int max) {
  return min + RANDOM_FLOAT * (max - min);
}

void Utility::diamondStep(float *array2D, int m_terrainSize, int m_rectSize,
                          float curHeight) {}

void Utility::squareStep(float *array2D, int m_terrainSize, int m_rectSize,
                         float curHeight) {}

void Utility::PopulateBuffers(float *array2D, std::vector<Vertex> &vertices,
                              std::vector<GLuint> &indices, int size,
                              float m_worldScale) {
  for (int i = 0; i < size; i++) {
    int z = i * size;
    for (int j = 0; j < size; j++) {
      vertices.push_back(Vertex(
          glm::vec3(j * m_worldScale, *(array2D + z + j), i * m_worldScale),
          glm::vec3(1.0, 1.0, 1.0)));
    }
  }

  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - 1; j++) {
      indices.push_back(i * size + j);
      indices.push_back((i + 1) * size + j);
      indices.push_back(i * size + j + 1);
      indices.push_back((i + 1) * size + j + 1);
      indices.push_back(i * size + j + 1);
      indices.push_back((i + 1) * size + j);
    }
  }
}

void Utility::getMinMaxValue(float *array2D, int size, float &min, float &max) {
  min = *array2D;
  max = *array2D;

  for (int i = 0; i < size; i++) {
    int z = i * size;
    for (int j = 0; j < size; j++) {
      max = (*(array2D + z + j) > max) ? *(array2D + z + j) : max;
      min = (*(array2D + z + j) < min) ? *(array2D + z + j) : min;
    }
  }
}

void Utility::Normalize(float *array2D, int size, int min, int max,
                        int minHeight, int maxHeight) {

  float delta_height = maxHeight - minHeight;
  float min_max_del = max - min;

  for (int i = 0; i < size; i++) {
    int z = i * size;
    for (int j = 0; j < size; j++) {
      *(array2D + z + j) =
          ((*(array2D + z + j) - min) / min_max_del) * delta_height + minHeight;
    }
  }
}
