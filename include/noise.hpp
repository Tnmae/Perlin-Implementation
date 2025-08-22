#ifndef NOISE_HPP
#define NOISE_HPP

#include <cmath>
#include <iostream>

#define RANDOM_VALUE ((float)rand() / (float)(RAND_MAX))

typedef struct {
  float x;
  float y;
} vector2D;

extern int permutation[512];

void swap(int array[], int idx1, int idx2);

void shuffle(int arrayToShuffle[]);

extern void makePermutation();

vector2D getConstantVector(int valueFromPerm);

inline float dot(vector2D constantVector, vector2D gradientVector) {
  return constantVector.x * gradientVector.x +
         constantVector.y * gradientVector.y;
}

inline double fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

inline double lerp(float t, float u, float v) { return u + t * (v - u); }

float Noise2D(float x, float y);

float valueNoise2D(float x, float y);

#endif /*NOISE_HPP*/
