#include "utils.hpp"
#include "cvector.hpp"
Mat read_image()
{
    std::string path="";
    std::cout<<"Please enter the path for image";
    std::cin>>path;
    Mat image = imread(path);
    return image;
}

unsigned char normalization(int oldmin,int oldmax,int newmin,int newmax,unsigned char value)
{
   int oldrange=oldmax-oldmin;
   int newrange=newmax-newmin;
    return (newrange*(value-oldmin)/oldrange)+newmin;
}

cvector<unsigned char> vectorizzation(Mat image)
{
        cvector<unsigned char> vector;
    if (image.isContinuous()) {
        vector.assign((unsigned char*)image.datastart, (unsigned char*)image.dataend);
    } else {
        for (int i = 0; i < image.rows; ++i) {
            vector.insert(vector.end(), image.ptr<unsigned char>(i), image.ptr<unsigned char>(i)+image.cols);
  }
            }
    return vector;
}

void vectorization_2d(int m,int n,cvector<int> temp, cvector< cvector<int> >& matrix) {
          for (int i = 0; i < matrix.size(); i++)
      {
          for (int j = 0; j < matrix[i].size(); j++)
          {
            matrix[i][j] = temp[j + 3*i];
          }
      }
}

