// #include "image.hpp"
#include "cvector.hpp"

namespace img
{
    cvector<cvector<int>> filter(cvector<cvector<int>> img, cvector<cvector<int>> mask)
    {
        cvector<cvector<int>> fltr;
        size_t img_rows = img.size();
        size_t img_cols = img[0].size();
        size_t mask_rows = mask.size();
        size_t mask_cols = mask[0].size();
        for (size_t row = 0; row < (img_rows - mask_rows + 1); row++)
        {
            cvector<int> row_px;
            for (size_t col = 0; col < (img_cols - mask_cols + 1); col++)
            {
                cvector<cvector<int>> sub = img.range(row, row + mask_rows, col, col + mask_cols);
                int px = 0;
                for (size_t mask_row = 0; mask_row < mask_rows; mask_row++)
                {
                    px += sub[mask_row].dot(mask[mask_row]);
                }
                row_px.push_back(px);
            }
            fltr.push_back(row_px);
        }
        return fltr;
    }
<<<<<<< Updated upstream
=======

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

    void histogram_equalization(Image eq_img)
    {
        int hist [256]={0};
        Image equalized = eq_img.mat.clone();
        Image hsv = convert(equalized, "bgr", "hsv");
        cvector<Image> splt = split(hsv);
        for (int i = 0; i < equalized.mat.rows * equalized.mat.cols; i++)
          hist[(int)(splt[2].pixels[i])] = hist[(int)(splt[2].pixels[i])] +1;
        int sum=0;
        int pdf [256]={0};
        int map [256]={0};
        for (int i = 0; i < 256; i++)
        {
        sum= sum +hist[i];
        pdf[i]=sum;
        }
        for (int i = 0; i < 256; i++)
        {
        map[i]=(int)((pdf[i]-pdf[0]-0.f)*255/(pdf[255]-pdf[0]));
        }
            for (int i = 0; i < 256; i++)
        {
        std::cout<<map[i]<<std::endl;
        }
        for (int i = 0; i < equalized.mat.rows * equalized.mat.cols; i++)
            splt[2].mat.data[i] =map[(int)(splt[2].pixels[i])];
        Image merged = merge(splt);
        Image bgr = convert(merged, "hsv", "bgr");
        bgr.display();

    }


>>>>>>> Stashed changes
}