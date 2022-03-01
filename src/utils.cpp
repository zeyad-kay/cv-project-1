#include "utils.hpp"

Mat read_image(std::string path)
{
    Mat image = imread(path);;
    return image;
}

unsigned char normalization(int oldmin,int oldmax,int newmin,int newmax,unsigned char value)
{
   int oldrange=oldmax-oldmin;
   int newrange=newmax-newmin;
    return (newrange*(value-oldmin)/oldrange)+newmin;    
}

std::vector<unsigned char> vectorizzation(Mat image)
{
        std::vector<unsigned char> vector;
    if (image.isContinuous()) {
        vector.assign((unsigned char*)image.datastart, (unsigned char*)image.dataend);
    } else {
        for (int i = 0; i < image.rows; ++i) {
            vector.insert(vector.end(), image.ptr<unsigned char>(i), image.ptr<unsigned char>(i)+image.cols);
  }
            }
    return vector;
}

unsigned char ** mat_to_2d(Mat img)
{
    uchar **array = new uchar*[img.rows];
    for (int i=0; i<img.rows; ++i)
    array[i] = new uchar[img.cols*img.channels()];

    for (int i=0; i<img.rows; ++i)
    array[i] = img.ptr<uchar>(i);
 return array;
} 
