#include "add_noise.hpp"
#include <opencv2/opencv.hpp>
#include <random>

    img::Image add_noise(img::Image source , char type ,uchar noise_factor){

    cv::Mat source_mat = source.mat.clone();

    img::Image noisy_image;
    std::default_random_engine generator;
    std::normal_distribution<double> gauss_random(0, 1);
    std::uniform_real_distribution<double> uniform_random(-1,1);
    std::uniform_int_distribution<int> sp_random(0,100);

    int channels_number = source_mat.channels();
    int cols_number = source_mat.cols;
    int rows_number = source_mat.rows;
    double noise = 0.f;
    int random_salt;
    
    for(int row=0;row<rows_number;row++){
    for(int col=0;col<cols_number;col++){
        if(type == 'G'){
            noise = gauss_random(generator)*noise_factor;
        }
        else if(type == 'U'){
            noise = uniform_random(generator)*noise_factor;
        }
        else if(type == 'S'){
            random_salt = sp_random(generator) ;
        }
        for(int ch=0;ch<channels_number;ch++){
            if (type == 'S'){
                if(random_salt<noise_factor){
                    source_mat.at<cv::Vec3b>(row,col)[ch] =  0;
                    }
                else if(random_salt>(100-noise_factor)){
                    source_mat.at<cv::Vec3b>(row,col)[ch] =  255;
                }
            }
            else{
            source_mat.at<cv::Vec3b>(row,col)[ch] +=  (uchar)noise;
            }
        }
    }
    }
    return img::Image(source_mat);
}