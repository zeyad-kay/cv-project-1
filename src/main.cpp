#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.hpp"
#include "cvector.hpp"
#include "histogram.hpp"

using namespace cv;
using namespace img;

int main(int argc, char **argv)
{    
  Image image = Image("C:\\Users\\abdoz\\Documents\\CV\\test\\lenna.png");
image.display("original");
// part 1 & 2
  Image noisy_Salt = add_noise(image,"Salt",5);
  Image noisy_Gaussian = add_noise(image,"Gaussian",20);
  Image noisy_Uniform = add_noise(image,"Uniform",20);
  Image filtered_Median = noise_filter(noisy_Salt,3,"Median");
  Image filtered_Gaussian = noise_filter(noisy_Salt,3,"Gaussian");
  Image filtered_Mean = noise_filter(noisy_Salt,3,"Mean");
  noisy_Salt.display("noisy_Salt");
  noisy_Gaussian.display("noisy_Gaussian");
  noisy_Uniform.display("noisy_Uniform");
  filtered_Median.display("filtered_Median");
  filtered_Gaussian.display("filtered_Gaussian");
  filtered_Mean.display("filtered_Mean");


 // part 3 edges
  Image gray = convert(image, "bgr", "gray");
  // sobel
  Image sbl = sobel(gray,1,1);
  sbl.display("sobel");

  // prewitt
  Image prt = prewitt(gray,1,1);
  prt.display("prewitt");

  // roberts
  Image rob = roberts(gray,1,1);
  rob.display("roberts");

  //4-Histogram and distribution curve
    Plot_Histogram(image, "color");
    plot_Distribution_curve(image,"color");

  // part 5) equalization

  Image eq_img = histogram_equalization(image);
  eq_img.display("equalized image");

  // part 6) normalize image:
    Image hsv = convert(image, "bgr", "hsv");
    cvector<Image> splt = split(hsv);
    
    splt[2] = normalize(splt[2],0,50);
    Image merged  = merge(splt);
    Image bgr = convert(merged, "hsv", "bgr");
    bgr.display("normalized image");
  return 0;
}
