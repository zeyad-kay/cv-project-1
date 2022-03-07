#include "utils.hpp"

unsigned char normalization(int oldmin, int oldmax, int newmin, int newmax, unsigned char value)
{
    int oldrange = oldmax - oldmin;
    int newrange = newmax - newmin;
    return (newrange * (value - oldmin) / oldrange) + newmin;
}

cvector<cvector<double>> gaussian_kernel(int size, double std)
{
    double gaussian_value;
    double normalization_sum = 0;
    cvector<cvector<double>> filter;
    for (int row = -size / 2; row <= size / 2; row++)
    {
        cvector<double> row_vector;
        for (int col = -size / 2; col <= size / 2; col++)
        {
            gaussian_value = (1 / (2 * (22 / 7) * pow(std, 2))) * exp(-(pow(row, 2) + pow(col, 2)) / (2 * pow(std, 2)));
            normalization_sum += gaussian_value;
            row_vector.push_back(gaussian_value);
        }
        filter.push_back(row_vector);
    }

    return filter;
}