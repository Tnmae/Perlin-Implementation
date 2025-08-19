#include "../include/base_utils.hpp"

#define RANDOM_FLOAT ((float)rand() / (float)RAND_MAX)

float RandomFloatRange(float min, float max) {
  return min + RANDOM_FLOAT * (max - min);
}

void Utility::diamondStep(float *array2D, int m_terrainSize, int m_rectSize,
                          float curHeight) {

  int halfRectSize = m_rectSize / 2;

  for (int i = 0; i < m_terrainSize; i += m_rectSize) {
    for (int j = 0; j < m_terrainSize; j += m_rectSize) {
      int next_x = (j + m_rectSize) % m_terrainSize;
      int next_z = (i + m_rectSize) % m_terrainSize;

      float topLeft = *(array2D + i * m_terrainSize + j);
      float topRight = *(array2D + i * m_terrainSize + next_x);
      float bottomLeft = *(array2D + next_z * m_terrainSize + j);
      float bottomRight = *(array2D + next_z * m_terrainSize + next_x);

      int mid_x = j + halfRectSize;
      int mid_z = i + halfRectSize;

      float randValue = RandomFloatRange(-curHeight, curHeight);

      float midPoint = (topLeft + topRight + bottomLeft + bottomRight) / 4.0f;

      *(array2D + mid_z * m_terrainSize + mid_x) = midPoint + randValue;
    }
  }
}

void Utility::squareStep(float *array2D, int m_terrainSize, int m_rectSize,
                         float curHeight) {
  int halfRectSize = m_rectSize / 2;

  for (int i = 0; i < m_terrainSize; i += m_rectSize) {
    for (int j = 0; j < m_terrainSize; j += m_rectSize) {
      int next_x = (j + m_rectSize) % m_terrainSize;
      int next_z = (i + m_rectSize) % m_terrainSize;

      int mid_x = j + halfRectSize;
      int mid_z = i + halfRectSize;

      int prev_mid_x = (j - halfRectSize + m_terrainSize) % m_terrainSize;
      int prev_mid_z = (i - halfRectSize + m_terrainSize) % m_terrainSize;

      float curTopLeft = *(array2D + i * m_terrainSize + j);
      float curTopRight = *(array2D + i * m_terrainSize + next_x);
      float curCenter = *(array2D + mid_z * m_terrainSize + mid_x);
      float prevYCenter = *(array2D + prev_mid_z * m_terrainSize + mid_x);
      float curBotLeft = *(array2D + next_z * m_terrainSize + j);
      float prevXCenter = *(array2D + mid_z * m_terrainSize + prev_mid_x);

      float curLeftMid =
          (curTopLeft + curCenter + curBotLeft + prevXCenter) / 4.0f +
          RandomFloatRange(-curHeight, curHeight);
      float curTopMid =
          (curTopLeft + curCenter + curTopRight + prevYCenter) / 4.0f +
          RandomFloatRange(-curHeight, curHeight);

      *(array2D + i * m_terrainSize + mid_x) = curTopMid;
      *(array2D + mid_z * m_terrainSize + j) = curLeftMid;
    }
  }
}

void Utility::PopulateBuffers(float *array2D, std::vector<Vertex> &vertices,
                              std::vector<GLuint> &indices, int size,
                              float m_worldScale) {
  for (int i = 0; i < size; i++) {
    int z = i * size;
    for (int j = 0; j < size; j++) {
      vertices.push_back(Vertex(glm::vec3(j * m_worldScale, *(array2D + z + j),
                                          -size + i * m_worldScale),
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

void Utility::Normalize(float *array2D, int size, float min, float max,
                        float minHeight, float maxHeight) {

  if (max == min)
    return;

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
