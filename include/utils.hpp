#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "cvector.hpp"
#include <cstdlib>
#include <cmath>
#include <math.h>

unsigned char normalization(int oldmin, int oldmax, int newmin, int newmax, unsigned char value);
cvector<cvector<double>> gaussian_kernel(int size, double std);
void RGBtoHSV(float fR, float fG, float fB, float *fH, float *fS, float *fV);
void HSVtoRGB(float *fR, float *fG, float *fB, float fH, float fS, float fV);
#endif