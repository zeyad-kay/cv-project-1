#ifndef __NOISE_FILTERS__
#define __NOISE_FILTERS__
#include <opencv2/opencv.hpp>
#include <cmath>
#include "Image.hpp"
#include "cvector.hpp"
#include <string.h>

cvector <cvector<double>> gaussian_kernal(int size, double std);
img::Image noise_filter(img::Image source,int size, std::string type  ,double std=1);
// img::Image noise_filter(img::Image source);

#endif