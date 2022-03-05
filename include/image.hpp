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
            void display(std::string title) const;
            void vectorize();
    };
    cvector<double> filter(const Image &img, cvector<cvector<double>> mask);
    Image merge(const cvector<Image> &imgs);
    Image convert(const Image &img, std::string from, std::string to);
    cvector<Image> split(const Image &img);
    cvector<uchar> normalize(cvector<double> &pixels, double min, double max);
    Image sobel(const Image &img, bool dx = true, bool dy = true);
    Image prewitt(const Image &img, bool dx = true, bool dy = true);
    Image roberts(const Image &img, bool dx = true, bool dy = true);
    cvector<uchar> scale(cvector<double> pixels);
};

#endif
