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

    void Image::display(std::string txt) const
    {
        cv::namedWindow(txt, cv::WINDOW_AUTOSIZE);
        cv::imshow(txt, this->mat);
        cv::waitKey(0);
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

    cvector<cvector<uchar>> Image::to_2d() const
    {
        cvector<cvector<uchar>> matrix(this->mat.rows, cvector<uchar>(this->mat.cols));
        for (int i = 0; i < this->mat.rows; i++)
        {
            for (int j = 0; j < this->mat.cols; j++)
            {
                matrix[i][j] = this->pixels[j + (this->mat.cols * i)];
            }
        }
        return matrix;
    }

    Image filter(const Image &img, cvector<cvector<uchar>> mask)
    {
        cvector<uchar> fltr;
        cvector<cvector<uchar>> mtrx = img.to_2d();
        size_t img_rows = mtrx.size();
        size_t img_cols = mtrx[0].size();
        size_t mask_rows = mask.size();
        size_t mask_cols = mask[0].size();

        for (size_t row = 0; row < (img_rows - mask_rows + 1); row++)
        {
            for (size_t col = 0; col < (img_cols - mask_cols + 1); col++)
            {
                cvector<cvector<uchar>> sub = mtrx.range(row, row + mask_rows, col, col + mask_cols);
                int px = 0;
                for (size_t mask_row = 0; mask_row < mask_rows; mask_row++)
                {
                    px += sub[mask_row].dot(mask[mask_row]);
                }
                fltr.push_back(px);
            }
        }
        return Image(fltr, (img_rows - mask_rows + 1), (img_cols - mask_cols + 1), img.mat.type());
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

}