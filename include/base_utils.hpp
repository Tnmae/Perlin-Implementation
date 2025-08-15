#ifndef BASE_UTILS_HPP
#define BASE_UTILS_HPP

#include "VBO.hpp"
#include <iostream>
#include <vector>

namespace Utility {
void initArray2D(int *array2D);

template <typename type> void initArray2D(type *array2D, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; i < size; j++) {
      *(array2D + i * size + j) = (type)0.0f;
    }
  }
}

void getMinMaxValue(float *array2D, int size, float &min, float &max);

void PopulateBuffers(float *array2D, std::vector<Vertex> &vertices,
                     std::vector<GLuint> &indices, int size,
                     float m_worldScale = 1.0f);

void diamondStep(float *array2D, int m_terrainSize, int m_rectSize,
                 float curHeight);

void squareStep(float *array2D, int m_terrainSize, int m_rectSize,
                float curHeight);

void Normalize(float *array2D, int size, int min, int max, int minHeight,
               int maxHeight);

}; // namespace Utility

#endif /* BASE_UTILS_HPP */
