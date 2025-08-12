#ifndef NOISE_HPP
#define NOISE_HPP

#include <iostream>

#define DEFAULT_OFFSET 1.00

namespace Noise {
void Perlin2D(float *array2D, double offset = DEFAULT_OFFSET);
void OpenSimplex2D();
void Value();
}; // namespace Noise

#endif /* NOISE_HPP */
