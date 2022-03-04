#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.hpp"
#include "cvector.hpp"

using namespace cv;
using namespace img;

int main(int argc, char **argv)
{
  // Read image
  Image image = Image("C:\\Users\\zeyad\\Desktop\\cv-project-1\\lenna.png");
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
  
  // gray.display();

  return 0;
}
