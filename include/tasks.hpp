#ifndef __TASKS_HPP__
#define __TASKS_HPP__
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include "utils.hpp"
using namespace cv;
void normalize_image(std::vector<uchar>array,int newmin,int newmax);

#endif