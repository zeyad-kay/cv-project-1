#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils.hpp"
#include "tasks.hpp"
using namespace cv;

int main(int argc, char** argv )
{
    // Read image
    Mat image;
    std::string path="";
    std::cout<<"Please enter the path for image";
    std::cin>>path;
    image = read_image(path);

    // split channels     
    Mat chnnels[3];
    split(image, chnnels);//splitting images into 3 different channels//  
    Mat b = chnnels[0];//loading blue channels//
    Mat g = chnnels[1];//loading green channels//
    Mat r = chnnels[2];//loading red channels//  

    // vectorization
    std::vector<unsigned char> array =vectorizzation(image);

    // Normalization Task
    normalize_image(array,100,255);

        return 0;
}