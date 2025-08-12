#ifndef BASE_UTILS_HPP
#define BASE_UTILS_HPP

#include "VBO.hpp"
#include <iostream>
#include <vector>

namespace Utility {
void initArray2D(int *array2D);

template <typename type> void initArray2D(int *array2D, type value);

template <typename type> void setValueArray2D(int *array2D, type value);

void getMinMaxValue(int *array2D);

void PopulateBuffers(std::vector<Vertex> vertices, std::vector<GLuint> indices);

void diamondStep(float *array2D, int m_terrainSize, int m_rectSize,
                 float curHeight);

void squareStep(float *array2D, int m_terrainSize, int m_rectSize,
                float curHeight);

}; // namespace Utility

#endif /* BASE_UTILS_HPP */
