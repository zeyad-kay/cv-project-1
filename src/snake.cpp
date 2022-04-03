#include "snake.hpp"

double points_distance(int x1, int y1, int x2, int y2){

    return sqrt(pow((x2 - x1),2) + pow((y2 - y1),2));
}
double avg_distance(int* x_points, int* y_points, int points_n){
    double distance_sum = 0;
    for(int i=0;i<points_n;i++){
        int next_point = i+1;
        if(i == points_n-1){
            next_point = 0;
        }

        double distance = points_distance(x_points[i],y_points[i],x_points[next_point],y_points[next_point]);
        distance_sum += distance;

    }
    double avg_distance = distance_sum/points_n;
    return avg_distance;
}

double internal_energy(int* x_points, int* y_points,int points_n, double alpha, double beta){
    double curv_sum = 0;
    double second_drev =0;
    double cont_sum = 0;
    double first_driv = 0;
    double avg_dist = avg_distance(x_points,y_points,points_n);
    for(int i=0;i<points_n;i++){
        int next_point = i+1;
        int prev_point = i-1;
        if(i == points_n-1){
            next_point = 0;
        }
        else if(i == 0){
            prev_point = points_n-1;
        }
        first_driv =  points_distance(x_points[i],y_points[i],x_points[next_point],y_points[next_point]);
        cont_sum += pow((first_driv-avg_dist),2);
        second_drev = pow((x_points[next_point]- 2 * x_points[i]+ x_points[prev_point]),2) + pow((y_points[next_point]- 2 * y_points[i]+ y_points[prev_point]),2);
        curv_sum += second_drev;
    }
    double energy = alpha * cont_sum + beta * curv_sum;
    return energy;
}

img::Image external_energy(img::Image source){
    img::Image filtered_Gaussian = img::noise_filter(source, 3, "Gaussian");
    img::Image gray = img::convert(filtered_Gaussian, "bgr", "gray");
    // cv::Sobel(gray.mat,gray.mat,CV_8UC1,1,1);
    return img::Image(img::scale(img::sobel(gray, 1, 1)), gray.mat.rows - 2, gray.mat.rows - 2, CV_8UC1);
    // return gray;
}

void greedy_contour(img::Image source, int iterations ,int alpha, int beta, int gamma,int* x_points, int* y_points, int points_n, int window_size){
    img::Image sobel_energy = external_energy(source);
    cvector<cvector<int>> window = window_neighbours(window_size);
    int current_x[180];
    int current_y[180];
    std::copy(x_points,x_points + points_n,current_x);
    std::copy(y_points,y_points + points_n,current_y);
    int point_energy;
    int min_energy;
    int min_index;
    int movements = 0;
    int iteration = 0;
    bool loob = true;
    int threshold = 5;
    int neighbours_size = pow(window_size,2);
    while(loob){
        for(int i=0;i<points_n;i++){
            for(int j=0;j<neighbours_size;j++){
                current_x[i] = x_points[i] + window[j][0];
                current_y[i] = y_points[i] + window[j][1];
                if(current_x[i] < sobel_energy.mat.rows   && current_x[i] > 0 && current_y[i] > 0 && current_y[i] < sobel_energy.mat.cols){
                    // point_energy = sobel_energy.mat.at<uchar>(current_x[i],current_y[i]) * -1 * gamma;
                    point_energy = sobel_energy.mat.at<uchar>(current_x[i],current_y[i]) * -1 * gamma + internal_energy(current_x, current_y,points_n, alpha, beta);
                    // std::cout<< point_energy<<"$$";
                    if(j==0){
                        min_energy = point_energy;
                        min_index = j;
                    }
                    else{
                        if(point_energy < min_energy){
                            min_energy = point_energy;
                            min_index = j;
                        }
                    }
                }
            }
            x_points[i] = x_points[i] + window[min_index][0];
            y_points[i] = y_points[i] + window[min_index][1];
            if(window[min_index][0] != 0 || window[min_index][1] != 0){
                movements++;
            }
        }
        iteration++;
        std::cout<<iteration;

        if(iteration > iterations || movements < threshold){
            loob = false;
        }
    }
}

cvector<cvector<int>> window_neighbours(int size){
    cvector<cvector<int>> window;
    cvector<int> point;
    
    for(int i = -size/2; i <= size/2;i++ ){
        
        for(int j = -size/2; j <= size/2;j++ ){
            point = {i,j};
            window.push_back(point);
        }
    }
    return window;
}

