#include "../include/noise.hpp"

#define RANDOM_VALUE ((float)rand() / (float)RAND_MAX)

typedef struct {
  float x;
  float y;
} vector2D;

void Noise::Perlin2D(float *array2D, double offset) {
  vector2D vectorArray2D[800][800];

  for (int i = 0; i < 800; i++) {
    for (int j = 0; j < 800; j++) {
      vectorArray2D[i][j] = {(float)i, (float)j};
    }
  }
}
