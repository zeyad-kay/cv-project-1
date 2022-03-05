#ifndef __ADD_NOISE__
#define __ADD_NOISE__
#include <opencv2/opencv.hpp>
#include <random>
#include "Image.hpp"
#include <string.h>

img::Image add_noise(img::Image source ,std::string type ,uchar noise_factor);

#endif


