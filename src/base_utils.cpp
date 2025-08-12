#include "../include/base_utils.hpp"

#define RANDOM_FLOAT ((float)rand() / (float)RAND_MAX)

float RandomFloatRange(int min, int max) {
  return min + RANDOM_FLOAT * (max - min);
}

void Utility::diamondStep(float *array2D, int m_terrainSize, int m_rectSize,
                          float curHeight) {}

void Utility::squareStep(float *array2D, int m_terrainSize, int m_rectSize,
                         float curHeight) {}
