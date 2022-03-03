#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils.hpp"
#include "tasks.hpp"
#include "cvector.hpp"
using namespace cv;

int main(int argc, char** argv )
{
    // Read image
    Mat image;
    image = read_image();

    // split channels     
    Mat chnnels[3];
    split(image, chnnels);//splitting images into 3 different channels//  
    Mat b = chnnels[0];//loading blue channels//
    Mat g = chnnels[1];//loading green channels//
    Mat r = chnnels[2];//loading red channels//  

    // vectorization
    cvector<unsigned char> array =vectorizzation(image);

    // Normalization Task
    normalize_image(array,100,255);

    // 2d vectorization
    /*
    auto N = 3;	// num of rows
    auto M = 3; // num of cols in each row
    auto default_value = 1; // default value of all int elements
    cvector<cvector<int>> matrix(N, cvector<int>(M, default_value));
    cvector<int>temp(9,0);  //1d vector 
      temp[0] = 1;
      temp[1] = 2;
      temp[2] = 3;
      temp[3] = 4;
      temp[4] = 5;
      temp[5] = 6;
      temp[6] = 7;
      temp[7] = 8;
    vectorization_2d(N,M, temp,matrix);
    */
        return 0;
}



    // print 2d vector
    /*
      for (int i = 0; i < N; i++)
      {
          for (int j = 0; j <M; j++)
          {
            std::cout << matrix[i][j] << " ";
          }
          std::cout << std::endl;
      }
      */