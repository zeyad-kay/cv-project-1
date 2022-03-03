#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include "cvector.hpp"
using namespace cv;
Mat read_image();
unsigned char normalization(int oldmin,int oldmax,int newmin,int newmax,unsigned char value);
cvector<unsigned char> vectorizzation(Mat image);
void vectorization_2d(int m,int n,cvector<int> temp, cvector< cvector<int> >& matrix);
#endif