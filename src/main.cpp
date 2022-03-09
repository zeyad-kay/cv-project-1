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
    
  Image image = Image("H:/cv-project-1/lennagray.png");

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
  
    /*Histogram and distribution curve
    Mat image = imread("image path");
    Plot_Histogram(image, "color");
    plot_Distribution_curve(image,"color");
    */
  return 0;
}
