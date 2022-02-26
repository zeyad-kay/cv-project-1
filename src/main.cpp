#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main(int argc, char** argv )
{

    Mat image;
    Mat chnnels[3];
    image = imread("C:/Users/abdoz/Documents/CV/test/lenna.png");
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    split(image, chnnels);//splitting images into 3 different channels//  
    Mat b = chnnels[0];//loading blue channels//
    Mat g = chnnels[1];//loading green channels//
    Mat r = chnnels[2];//loading red channels//  
    imshow("Blue Channel",b);//showing Blue channel//
    imshow("Green Channel",g);//showing Green channel//
    imshow("Red Channel",r);//showing Red channel//
    imshow("Actual_Image", image);//showing actual image//
    waitKey(0);//wait for key stroke
    destroyAllWindows();//closing all windows//
    std::vector<uchar> array;
    if (b.isContinuous()) {
        array.assign((uchar*)b.datastart, (uchar*)b.dataend);
    } else {
        for (int i = 0; i < b.rows; ++i) {
            array.insert(array.end(), b.ptr<uchar>(i), b.ptr<uchar>(i)+b.cols);
  }
}

    int rows =  sizeof array / sizeof array[0]; // 2 rows  

    int cols = sizeof array[0] / sizeof(int); // 5 cols
    //for (auto i: array)
        std::cout <<array.size();
    return 0;
}