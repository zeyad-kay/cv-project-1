#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.hpp"
#include "cvector.hpp"

using namespace cv;
using namespace img;

int main(int argc, char **argv)
{
  Image image = Image("images/lenna.png");
  Image noisy = add_noise(image,"Salt",5);
  Image filtered = noise_filter(noisy,3,"Median");

  image.display("image");
  noisy.display("noisy");
  filtered.display("filtered");
  return 0;
}
