#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils.hpp"
#include "tasks.hpp"
#include "cvector.hpp"
using namespace cv;

int main(int argc, char** argv )
{
<<<<<<< Updated upstream
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
=======
  // Read image
  Image image = Image("C:\\Users\\abdoz\\Documents\\GitHub\\cv-project-1\\mashromcolor.PNG");
  // image.display();

  cvector<int> mask = {1, 2, 3, 4};

  std::cout << mask << "\n";
  std::cout << "Squared: "<< (mask * mask) << "\n";
  std::cout << "Multipled by 2"<< (mask * 2) << "\n";
  std::cout << "Added by 2"<< (mask + 2) << "\n";
  
  cvector<cvector<int>> mask2d = {
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1},
  };
  
  std::cout << mask << "\n";
  std::cout << "Squared: "<< (mask2d + mask2d) << "\n";
  // std::cout << "Multipled by 2"<< (mask2d * 2) << "\n";
  // std::cout << "Added by 2"<< (mask2d + 2) << "\n";

  Image hsv = convert(image, "bgr", "hsv");

  // return 3 channels of image (h,s,v) or (b,g,r)
  cvector<Image> splt = split(hsv);

  // merge 3 channels of image to 1 image
  Image merged = merge(splt);

  Image bgr = convert(merged, "hsv", "bgr");
 
  // bgr.display();
  
  Image gray = convert(merged, "bgr", "gray");
  histogram_equalization(image);
  image.display();

  return 0;
>>>>>>> Stashed changes
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