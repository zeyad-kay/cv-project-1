#include"tasks.hpp"
#include"cvector.hpp"
void normalize_image(cvector<uchar>array,int newmin,int newmax)
{
        int oldmin= int(*min_element(array.begin(), array.end()));
        int oldmax= int(*max_element(array.begin(), array.end()));
        int oldrange=oldmax-oldmin;
        int newrange=newmax-newmin;

        for (int i =0; i<array.size();i++)
        {
            array[i] = normalization(oldmin,oldmax,newmin,newmax,array[i]);
            
        }

        Mat m = Mat(512, 512, CV_8UC3);
        memcpy(m.data, array.data(),array.size()*sizeof(unsigned char));
        namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", m);
    waitKey(0);
}