#ifndef __HISTOGRAM_HPP__
#define __HISTOGRAM_HPP__

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std ;
using namespace cv;

void plot(int array[],string window_name ,Scalar color);
void calculate_Histogram(Mat Image, string image_type);
void Plot_Histogram(Mat Image,string image_type);
void plot_Distribution_curve(Mat Image,string image_type);
void calculate_Cumulative(Mat Image,string image_type);
void Plot_Cumulative(Mat Image,string image_type);



#endif