#include "../include/noise.hpp"

int permutation[512];

void swap(int array[], int idx1, int idx2) {
  int temp = array[idx1];
  array[idx1] = array[idx2];
  array[idx2] = temp;
}

void shuffle(int arrayToShuffle[]) {
  for (int i = 255; i > 0; i--) {
    int index = rand() % (i + 1);
    swap(arrayToShuffle, index, i);
  }
}

void makePermutation() {
  for (int i = 0; i < 256; i++) {
    permutation[i] = i;
  }

  shuffle(permutation);

  for (int i = 0; i < 256; i++) {
    permutation[i + 256] = permutation[i];
  }
}

vector2D getConstantVector(int valueFromPerm) {
  int h = valueFromPerm & 3;
  if (!h) {
    return vector2D{1.0f, 1.0f};
  } else if (h == 1) {
    return vector2D{1.0f, -1.0f};
  } else if (h == 2) {
    return vector2D{-1.0f, 1.0f};
  } else {
    return vector2D{-1.0f, -1.0f};
  }
}

float Noise2D(float x, float y) {
  int X = ((int)floor(x)) & 255;
  int Y = ((int)floor(y)) & 255;

  float xf = x - floor(x);
  float yf = y - floor(y);

  vector2D topRight = {xf - 1.0f, yf - 1.0f};
  vector2D topLeft = {xf, yf - 1.0f};
  vector2D bottomRight = {xf - 1.0f, yf};
  vector2D bottomLeft = {xf, yf};

  int valueTopRight = permutation[permutation[(X + 1)] + (Y + 1)];
  int valueTopLeft = permutation[permutation[(X)] + (Y + 1)];
  int valueBottomRight = permutation[permutation[(X + 1)] + (Y)];
  int valueBottomLeft = permutation[permutation[(X)] + (Y)];

  float dotTopRight = dot(getConstantVector(valueTopRight), topRight);
  float dotTopLeft = dot(getConstantVector(valueTopLeft), topLeft);
  float dotBottomRight = dot(getConstantVector(valueBottomRight), bottomRight);
  float dotBottomLeft = dot(getConstantVector(valueBottomLeft), bottomLeft);

  float u = fade(xf);
  float v = fade(yf);

  return (lerp(u, lerp(v, dotBottomLeft, dotTopLeft),
               lerp(v, dotBottomRight, dotTopRight))) *
         1.41421356f;
}
