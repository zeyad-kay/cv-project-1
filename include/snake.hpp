#ifndef __SNAKE__
#define __SNAKE__
#include <cmath>
#include "cvector.hpp"
#include "image.hpp"
#include <stdio.h>



double avg_distance(int* x_points, int* y_points, int points_n);
cvector<cvector<int>> window_neighbours(int size);
void greedy_contour(img::Image source, int iterations ,int alpha, int beta, int gamma,int* x_points, int* y_points, int points_n, int window_size);

#endif