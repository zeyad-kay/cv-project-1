#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <opencv2/opencv.hpp>
#include "cvector.hpp"
#include <string.h>

namespace img
{
    class Image
    {
        public:
            cv::Mat mat;
            cvector<uchar> pixels;
            Image(){};
            Image(std::string path);
            Image(cv::Mat mat);
            Image(cvector<uchar> pixels, size_t rows, size_t cols, int type);
            void display() const;
            void vectorize();
            cvector<cvector<uchar>> Image::to_2d() const;
    };
    Image filter(const Image &img, cvector<cvector<uchar>> mask);
    Image merge(const cvector<Image> &imgs);
    Image convert(const Image &img, std::string from, std::string to);
    cvector<Image> split(const Image &img);
    Image normalize(Image &img, int min, int max);
    void histogram_equalization(Image eq_img);
};

#endif