#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "cvector.hpp"

unsigned char normalization(int oldmin, int oldmax, int newmin, int newmax, unsigned char value);
cvector<cvector<double>> gaussian_kernel(int size, double std);

#endif