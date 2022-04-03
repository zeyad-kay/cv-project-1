#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.hpp"
#include "cvector.hpp"
#include "histogram.hpp"
#include "utils.hpp"
#include "snake.hpp"
#include <math.h>
#include <cstdlib>
#include <cmath>


using namespace cv;
using namespace img;


void circle_contour(cv::Point center, double radius, int numberOfPoints, int *x_cooridinates, int *y_cooridinates)
{
    std::vector<double> mag = {radius};
    double current_angle = 0;
    double resolution = 360 / (double)numberOfPoints;
    std::cout << resolution << std::endl;
    for (int i = 0; i < numberOfPoints; i++)
    {
        std::vector<double> angle = {current_angle};
        std::vector<double> x = {};
        std::vector<double> y = {};
        cv::polarToCart(mag, angle, x, y, true);
        x_cooridinates[i] = (int) (x[0] + center.x);
        y_cooridinates[i] = (int) (y[0] + center.y);
        current_angle += resolution;
    }
}

void draw_contour(cv::Mat Image, int numberOfPoints, int *x_cooridinates, int *y_cooridinates)
{
  int next;
    for (int i = 0; i < numberOfPoints; i++)

    {
        next = i+1;
        if(i == numberOfPoints-1){
          next = 0;
        }
        line(Image, cv::Point(x_cooridinates[i], y_cooridinates[i]), cv::Point(x_cooridinates[next], y_cooridinates[next]), cv::Scalar(255, 0, 0), 2);
    }
}
int main(int argc, char **argv)
{




  Image image = Image("H:/sbme/CV/cv-project-1/images/coin.jpeg");
  int points = 80;
  cv::Size sz = image.mat.size();
  int x_cooridinates[80];
  int y_cooridinates[80];
  circle_contour(Point(sz.width / 2,sz.height / 2),150,points,x_cooridinates,y_cooridinates);
  // coin
  // 10, 0.4, 20
  greedy_contour(image, 100 ,2, 0.9, 20,x_cooridinates, y_cooridinates, points, 5);
  draw_contour(image.mat,points,x_cooridinates,y_cooridinates);
  image.display("a");
  

  // drawContour(image.mat);
  // greedy_contour(image, 60 ,1, 1, 100,x_cooridinates, y_cooridinates, 180, 5);
  // for (int i = 0; i <= 180; i++)
  //   {
  //       int next = i + 1;
  //       if(i == 179){
  //         next = 0;
  //       }
  //       line(image.mat, Point((x_cooridinates[i]),(y_cooridinates[i]) ),  Point((x_cooridinates[next]), (y_cooridinates[next]) ), Scalar(255, 0, 0), 2);
            
  //   }
  // image.display("original");

  // image.display("original");
  // Image filtered_Gaussian = noise_filter(image, 3, "Gaussian");
  // Image gray = convert(filtered_Gaussian, "bgr", "gray");
  // Image hsv = convert(image, "bgr", "hsv");
  // cvector<Image> splt = split(hsv);

  // // // part 1 & 2
  // Image noisy_Salt = add_noise(image, "Salt", 5);
  // Image noisy_Gaussian = add_noise(image, "Gaussian", 20);
  // Image noisy_Uniform = add_noise(image, "Uniform", 20);
  // Image filtered_Median = noise_filter(noisy_Salt, 3, "Median");
  // Image filtered_Gaussian = noise_filter(noisy_Salt, 3, "Gaussian");
  // Image filtered_Mean = noise_filter(noisy_Salt, 3, "Mean");
  // noisy_Salt.display("noisy_Salt");
  // noisy_Gaussian.display("noisy_Gaussian");
  // noisy_Uniform.display("noisy_Uniform");
  // filtered_Median.display("filtered_Median");
  // filtered_Gaussian.display("filtered_Gaussian");
  // filtered_Mean.display("filtered_Mean");
  // std::cout<< (int)gray.mat.at<uchar>(0,0);
  // part 3 edges
  // sobel
  // Image source = Image(scale(sobel(gray, 1, 1)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1);
  // roberts
  // Image(scale(roberts(gray, 1, 1)), gray.mat.rows - 1, gray.mat.rows - 1, CV_8UC1).display("roberts");
  // // prewitt
  // Image(scale(prewitt(gray, 1, 1)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1).display("prewitt");
  // // canny
  // Image(scale(canny(gray, 20, 55)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1).display("canny");

  // //   //4-Histogram and distribution curve
  // Image gray_image = Image("D:\\sbme\\fourth year\\second term\\CV\\projects\\cv-project-1\\images\\lenna.png");
  // Plot_Histogram(gray_image, "grayscale");
  // plot_Distribution_curve(gray_image, "grayscale");

  // // part 5) equalization
  // Image eq_img = histogram_equalization(image);
  // eq_img.display("equalized image");

  // // part 6) normalize image:
  // splt[2] = normalize(splt[2], 0, 20);
  // Image merged = merge(splt);
  // Image bgr = convert(merged, "hsv", "bgr");
  // bgr.display("normalized image");

  // Image grayscaled_image = convert(image, "bgr", "gray");
  // // part 7) local and global thresholding
  // grayscaled_image.display("gray scale");
  // Image t = globalThreshold(grayscaled_image, 127, 255, THRESH_BIN);
  // t.display("global thresholding");
  // t = localThreshold(grayscaled_image, 255, THRESH_BIN);
  // t.display("local thresholding");

  // // part 8
  // // 8.1 (convert color image to gray)
  // // 8.2 (plot R,G,B Histograms with its cumulative curve)
  // Plot_Histogram(image, "color");
  // Plot_Cumulative(image, "color");

  // // part 9) low pass and high pass filter
  // grayscaled_image.display("gray_scaled image");
  // Image low_pass = PassFilter(grayscaled_image, 80, LOW_PASS_FILTER);
  // low_pass.display("low pass");
  // Image high_pass = PassFilter(grayscaled_image, 50, HIGH_PASS_FILTER);
  // high_pass.display("high pass");

  // // part 10) hyprid images
  // // images should be the same size and on channel
  // Image image1 = Image("D:\\sbme\\fourth year\\second term\\CV\\projects\\cv-project-1\\images\\snake1.jpeg");
  // Image grayscaled_image1 = convert(image1, "bgr", "gray");
  // grayscaled_image1.display("image 1");
  // Image image2 = Image("D:\\sbme\\fourth year\\second term\\CV\\projects\\cv-project-1\\images\\snake2.jpeg");
  // Image grayscaled_image2 = convert(image2, "bgr", "gray");
  // grayscaled_image2.display("image 2");
  // Image hyprid = hybridImages(grayscaled_image1, grayscaled_image2);
  // hyprid.display("hyprid");
  return 0;
}

    // draw a circle => (x - a)^2 + (y - b)^2 = r^2 || x = r * cos(s) , y = r * sin(s)
    
    //int a = 0, b = 0, r = 100;
    
    //cv::circle(Image,Point(256,200),50,Scalar(0,0,255),1,8,1);
