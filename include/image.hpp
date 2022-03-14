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
    cvector<double> sobel(const Image &img, bool dx = true, bool dy = true);
    cvector<double> prewitt(const Image &img, bool dx = true, bool dy = true);
    cvector<double> roberts(const Image &img, bool dx = true, bool dy = true);
    cvector<double> canny(const Image &img, double threshold1, double threshold2);
    cvector<uchar> scale(cvector<double> pixels);
    bool strong_edge(cvector<cvector<double>> &mtrx, int row, int col, double min, double max);
    Image normalize(Image &img, int min, int max);
    Image add_noise(Image &source, std::string type, uchar noise_factor);
    Image noise_filter(Image &source, int size, std::string type, double std=1);
    Image histogram_equalization(Image &eq_img);
};

#endif