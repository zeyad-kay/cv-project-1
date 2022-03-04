#ifndef __ADD_NOISE__
#define __ADD_NOISE__
#include <opencv2/opencv.hpp>
#include <random>
#include "Image.hpp"

img::Image add_noise(img::Image source , char type ,uchar noise_factor);

#endif


