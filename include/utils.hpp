#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace cv;
Mat read_image(std::string path);
unsigned char normalization(int oldmin,int oldmax,int newmin,int newmax,unsigned char value);
std::vector<unsigned char> vectorizzation(Mat image);
unsigned char ** mat_to_2d(Mat image);
#endif