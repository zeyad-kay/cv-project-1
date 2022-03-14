#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.hpp"
#include "cvector.hpp"
#include "histogram.hpp"
#include "utils.hpp"
#include <math.h>
#include <cstdlib>
#include <cmath>
using namespace cv;
using namespace img;

int main(int argc, char **argv)
{
  Image image = Image("C:\\Users\\zeyad\\Desktop\\cv-project-1\\images\\lenna.png");

  image.display("original");
  Image gray = convert(image, "bgr", "gray");
  Image hsv = convert(image, "bgr", "hsv");
  cvector<Image> splt = split(hsv);

  // part 1 & 2
  Image noisy_Salt = add_noise(image, "Salt", 5);
  Image noisy_Gaussian = add_noise(image, "Gaussian", 20);
  Image noisy_Uniform = add_noise(image, "Uniform", 20);
  Image filtered_Median = noise_filter(noisy_Salt, 3, "Median");
  Image filtered_Gaussian = noise_filter(noisy_Salt, 3, "Gaussian");
  Image filtered_Mean = noise_filter(noisy_Salt, 3, "Mean");
  noisy_Salt.display("noisy_Salt");
  noisy_Gaussian.display("noisy_Gaussian");
  noisy_Uniform.display("noisy_Uniform");
  filtered_Median.display("filtered_Median");
  filtered_Gaussian.display("filtered_Gaussian");
  filtered_Mean.display("filtered_Mean");

  // part 3 edges

  // sobel
  Image(scale(sobel(gray, 1, 1)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1).display("sobel");
  // roberts
  Image(scale(roberts(gray, 1, 1)), gray.mat.rows - 1, gray.mat.rows - 1, CV_8UC1).display("roberts");
  // prewitt
  Image(scale(prewitt(gray, 1, 1)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1).display("prewitt");
  // canny
  Image(scale(canny(gray, 20, 55)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1).display("canny");

  // 4-Histogram and distribution curve
  Image gray_image = Image("E:\\Biomedical Drive\\cv tasks\\cv-project-1\\images\\mashromgray.png");
  Plot_Histogram(gray_image, "grayscale");
  plot_Distribution_curve(gray_image, "grayscale");

  // part 5) equalization

  Image eq_img = histogram_equalization(image);
  eq_img.display("equalized image");

  // part 6) normalize image:

  splt[2] = normalize(splt[2], 0, 20);
  Image merged = merge(splt);
  Image bgr = convert(merged, "hsv", "bgr");
  bgr.display("normalized image");

  // part 8
  // 8.1 (convert color image to gray)
  Image grayscaled_image = convert(image, "bgr", "gray");
  grayscaled_image.display("gray_scaled image");
  // 8.2 (plot R,G,B Histograms with its cumulative curve)
  Plot_Histogram(image, "color");
  Plot_Cumulative(image, "color");

  return 0;
}
