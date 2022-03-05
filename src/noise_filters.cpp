#include "noise_filters.hpp"

cvector <cvector<double>> gaussian_kernal(int size, double std){
    double gaussian_value;
    double normalization_sum = 0;
    cvector <cvector<double>> filter;
    for(int row = -size/2;row<=size/2;row++){
        cvector<double> row_vector;
        for(int col=-size/2;col<=size/2;col++){
            gaussian_value = (1/(2 * (22/7) * pow(std,2))) * exp(-(pow(row,2)+pow(col,2)) / (2 * pow(std,2)));
            normalization_sum += gaussian_value;
            row_vector.push_back(gaussian_value);
        }
        filter.push_back(row_vector);
    }
    
    return filter; 
}

img::Image noise_filter(img::Image source,int size, std::string type  ,double std){
    cvector <cvector<double>> filter = gaussian_kernal(size, std);
    double pixel_value = 0;
    int limit = size - 1;
    cvector<uchar> sub_matrix;
    cv::Mat source_mat = source.mat.clone();
    int channels_number = source_mat.channels();
    int cols_number = source_mat.cols;
    int rows_number = source_mat.rows;
    for (int src_row = 0;src_row<rows_number-limit;src_row++){
        for (int src_col = 0;src_col<cols_number-limit;src_col++){
            for (int ch=0;ch<channels_number;ch++){
                for (int flt_row = 0;flt_row<size;flt_row++){
                    for (int flt_col = 0;flt_col<size;flt_col++){
                        
                        if(type == "Gaussian"){
                        pixel_value += source_mat.at<cv::Vec3b>(src_row + flt_row, src_col + flt_col)[ch] * filter[flt_row][flt_col];
                        }
                        else if(type == "Mean" || type == "Median"){
                        sub_matrix.push_back(source_mat.at<cv::Vec3b>(src_row + flt_row, src_col + flt_col)[ch]);
                        }
                    }
                }

                if(type == "Gaussian"){
                source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = (uchar) pixel_value;
                pixel_value = 0;
                }
                else if(type == "Mean"){
                    source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = sub_matrix.mean();
                    sub_matrix.clear();
                }
                else if(type == "Median"){
                    source_mat.at<cv::Vec3b>(src_row, src_col)[ch] = sub_matrix.median();
                    sub_matrix.clear();
                }

            }        
        }
    }
    return img::Image(source_mat.colRange(0, cols_number - limit).rowRange(0, rows_number - limit));
}

// img::Image noise_filter(img::Image source){

//     cv::Mat source_mat = source.mat.clone();

//     size_t channels_number = source_mat.channels();
//     size_t cols_number = source_mat.cols;
//     size_t rows_number = source_mat.rows;
//     cvector<uchar> sub_matrix;
    
//     for(int row=1;row<rows_number-1;row++){
//     for(int col=1;col<cols_number-1;col++){

//         for(int ch=0;ch<channels_number;ch++){
//             sub_matrix = {source_mat.at<cv::Vec3b>(row-1,col-1)[ch],source_mat.at<cv::Vec3b>(row-1,col)[ch],source_mat.at<cv::Vec3b>(row-1,col+1)[ch],
//                         source_mat.at<cv::Vec3b>(row,col-1)[ch],source_mat.at<cv::Vec3b>(row,col)[ch],source_mat.at<cv::Vec3b>(row,col+1)[ch],
//                         source_mat.at<cv::Vec3b>(row+1,col-1)[ch],source_mat.at<cv::Vec3b>(row+1,col)[ch],source_mat.at<cv::Vec3b>(row+1,col+1)[ch]};
//             source_mat.at<cv::Vec3b>(row,col)[ch] = sub_matrix.median();
//         }
//     }
//     }
//     return img::Image(source_mat);
// }