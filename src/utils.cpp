#include "utils.hpp"

unsigned char normalization(int oldmin, int oldmax, int newmin, int newmax, unsigned char value)
{
    int oldrange = oldmax - oldmin;
    int newrange = newmax - newmin;
    return (newrange * (value - oldmin) / oldrange) + newmin;
}
