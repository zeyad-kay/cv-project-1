#include "cvector.hpp"
#include "image.hpp"
#include "utils.hpp"
#include <opencv2/opencv.hpp>

namespace img
{
    Image::Image(std::string path)
    {
        this->mat = cv::imread(path);
        this->vectorize();
    }

    Image::Image(cvector<uchar> pixels, size_t rows, size_t cols, int type)
    {
        this->mat = cv::Mat(rows, cols, type);
        memcpy(this->mat.data, pixels.data(), pixels.size() * sizeof(unsigned char));
        this->pixels = pixels;
    }

    Image::Image(cv::Mat mat)
    {
        this->mat = mat;
        this->vectorize();
    }

    void Image::display(std::string title) const
    {
        cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
        cv::imshow(title, this->mat);
    }

    void Image::vectorize()
    {
        if (this->mat.isContinuous())
        {
            this->pixels.assign((unsigned char *)this->mat.datastart, (unsigned char *)this->mat.dataend);
        }
        else
        {
            for (int i = 0; i < this->mat.rows; ++i)
            {
                this->pixels.insert(this->pixels.end(), this->mat.ptr<unsigned char>(i), this->mat.ptr<unsigned char>(i) + this->mat.cols);
            }
        }
    }

    cvector<double> filter(const Image &img, cvector<cvector<double>> mask)
    {
        size_t img_rows = img.mat.rows;
        size_t img_cols = img.mat.cols;
        size_t mask_rows = mask.size();
        size_t mask_cols = mask[0].size();

        // convert uchar to int to handle -ve values
        cvector<double> fltr(img.pixels.begin(), img.pixels.end());
        cvector<cvector<double>> mtrx = fltr.to_2d(img_rows, img_cols);
        fltr.clear();

        for (size_t row = 0; row < (img_rows - mask_rows + 1); row++)
        {
            for (size_t col = 0; col < (img_cols - mask_cols + 1); col++)
            {
                cvector<cvector<double>> sub = mtrx.range(row, row + mask_rows, col, col + mask_cols);
                double px = 0;
                for (size_t mask_row = 0; mask_row < mask_rows; mask_row++)
                {
                    px += sub[mask_row].dot(mask[mask_row]);
                }
                fltr.push_back(px);
            }
        }
        return fltr;
    }

    Image normalize(Image &img, int min, int max)
    {
        int oldmin = int(*std::min_element(img.pixels.begin(), img.pixels.end()));
        int oldmax = int(*std::max_element(img.pixels.begin(), img.pixels.end()));
        int oldrange = oldmax - oldmin;
        int newrange = max - min;
        cvector<uchar> array;
        for (int i = 0; i < img.pixels.size(); i++)
        {
            array.push_back(normalization(oldmin, oldmax, min, max, img.pixels[i]));
        }
        return Image(array, img.mat.rows, img.mat.cols, img.mat.type());
    }

    Image convert(const Image &img, std::string from, std::string to)
    {
        cv::Mat dest;
        if (from == "bgr" && to == "gray")
        {
            cv::cvtColor(img.mat, dest, cv::COLOR_BGR2GRAY);
        }
        else if (from == "gray" && to == "hsv")
        {
            cv::cvtColor(img.mat, dest, cv::COLOR_GRAY2BGR);
            convert(Image(dest), "bgr", "hsv");
        }
        else if (from == "bgr" && to == "hsv")
        {
            cv::cvtColor(img.mat, dest, cv::COLOR_BGR2HSV);
        }
        else if (from == "hsv" && to == "bgr")
        {
            cv::cvtColor(img.mat, dest, cv::COLOR_HSV2BGR);
        }
        else if (from == "gray" && to == "bgr")
        {
            cv::cvtColor(img.mat, dest, cv::COLOR_GRAY2BGR);
        }
        else
        {
            throw "Invalid conversion";
        }
        return Image(dest);
    }

    cvector<Image> split(const Image &img)
    {
        cv::Mat channels[3];
        split(img.mat, channels);
        cvector<Image> imgs = {channels[0], channels[1], channels[2]};
        return imgs;
    }

    Image merge(const cvector<Image> &imgs)
    {
        cv::Mat merged;
        cv::Mat cs[] = {imgs[0].mat, imgs[1].mat, imgs[2].mat};
        cv::merge(cs, 3, merged);
        return Image(merged);
    }

    Image sobel(const Image &img, bool dx, bool dy)
    {
        if (!dx && !dy)
        {
            throw "Must set dx or dy or both";
        }
        cvector<cvector<double>> x = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1},
        };
        cvector<cvector<double>> y = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1},
        };

        size_t dim = (img.mat.rows - 3 + 1) * (img.mat.cols - 3 + 1);
        cvector<double> gx(dim, 0);
        cvector<double> gy(dim, 0);
        if (dx)
        {
            gx = filter(img, x);
        }
        if (dy)
        {
            gy = filter(img, y);
        }
        cvector<uchar> res = scale(cvector<double>::mag(gx, gy));
        return Image(res, img.mat.rows - 3 + 1, img.mat.cols - 3 + 1, img.mat.type());
    }

    Image prewitt(const Image &img, bool dx, bool dy)
    {
        cvector<cvector<double>> x = {
            {1, 0, -1},
            {1, 0, -1},
            {1, 0, -1},
        };
        cvector<cvector<double>> y = {
            {1, 1, 1},
            {0, 0, 0},
            {-1, -1, -1},
        };

        size_t dim = (img.mat.rows - 3 + 1) * (img.mat.cols - 3 + 1);
        cvector<double> gx(dim, 0);
        cvector<double> gy(dim, 0);
        if (dx)
        {
            gx = filter(img, x);
        }
        if (dy)
        {
            gy = filter(img, y);
        }
        cvector<uchar> res = scale(cvector<double>::mag(gx, gy));
        return Image(res, img.mat.rows - 3 + 1, img.mat.cols - 3 + 1, img.mat.type());
    }

    Image roberts(const Image &img, bool dx, bool dy)
    {
        if (!dx && !dy)
        {
            throw "Must set dx or dy or both";
        }
        cvector<cvector<double>> x = {
            {1, 0},
            {0, -1},
        };
        cvector<cvector<double>> y = {
            {0, 1},
            {-1, 0},
        };
        size_t dim = (img.mat.rows - 2 + 1) * (img.mat.cols - 2 + 1);
        cvector<double> gx(dim, 0);
        cvector<double> gy(dim, 0);
        if (dx)
        {
            gx = filter(img, x);
        }
        if (dy)
        {
            gy = filter(img, y);
        }
        cvector<uchar> res = scale(cvector<double>::mag(gx, gy));
        return Image(res, img.mat.rows - 2 + 1, img.mat.cols - 2 + 1, img.mat.type());
    }

    Image canny(const Image &img, double threshold1, double threshold2)
    {
        if (!threshold1 || !threshold2)
        {
            throw "Must specify thresholds 1 and 2";
        }
        double max = std::max(threshold1, threshold2);
        double min = std::min(threshold1, threshold2);
        Image s = sobel(img, 1, 1);

        cvector<cvector<uchar>> mtrx = img.pixels.to_2d(img.mat.rows, img.mat.cols);
        cvector<uchar> pxs;
        for (int row = 0; row < mtrx.size(); row++)
        {
            for (int col = 0; col < mtrx[0].size(); col++)
            {
                if (strong_pixel(mtrx, row, col, min, max))
                {
                    pxs.push_back(mtrx[row][col]);
                }
                else
                {
                    pxs.push_back(0);
                }
            }
        }
        return Image(pxs, img.mat.rows, img.mat.cols, img.mat.type());
    }

    bool strong_pixel(cvector<cvector<uchar>> &mtrx, size_t row, size_t col, double min, double max)
    {
        if (mtrx[row][col] < min)
            return false;
        if (mtrx[row][col] >= max)
            return true;
        cvector<cvector<uchar>> sub = mtrx.range(row - 1, row + 2, col - 1, col + 2);
        for (int i = 0; i < sub.size(); i++)
        {
            for (int j = 0; j < sub[0].size(); j++)
            {
                if (sub[i][j] >= max)
                    return true;
            }
        }
        return false;
    }

    cvector<uchar> scale(cvector<double> pixels)
    {
        pixels = pixels.abs();
        cvector<uchar> res;
        double scaled = (255.0 / pixels.max());
        for (auto itr = pixels.begin(); itr != pixels.end(); itr++)
        {
            res.push_back((uchar)std::round((*itr) * scaled));
        }
        return res;
    }
}