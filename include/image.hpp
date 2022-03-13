#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <opencv2/opencv.hpp>
#include "cvector.hpp"
#include <string.h>


namespace img
{   
    typedef enum {
        THRESH_BIN,
        THRESH_BIN_INV
    }t_types;
    typedef enum {
        ADAPTIVE_THRESH_MEAN,
        ADAPTIVE_THRESH_GAUSSIAN
    }a_types;
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
    Image sobel(const Image &img, bool dx = true, bool dy = true);
    Image prewitt(const Image &img, bool dx = true, bool dy = true);
    Image roberts(const Image &img, bool dx = true, bool dy = true);
    Image canny(const Image &img, double threshold1, double threshold2);
    cvector<uchar> scale(cvector<double> pixels);
    bool strong_pixel(cvector<cvector<uchar>> &mtrx, int row, int col, double min, double max);
    Image normalize(Image &img, int min, int max);
    Image add_noise(Image &source, std::string type, uchar noise_factor);
    Image noise_filter(Image &source, int size, std::string type, double std = 1);
    Image histogram_equalization(Image &eq_img);
    Image globalThreshold(Image &img, float threshold, float mx_value, t_types thresholdType);
    Image localThreshold(Image &img, float mx_value, t_types thresholdType);
};

#endif