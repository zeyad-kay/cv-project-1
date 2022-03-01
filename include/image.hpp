#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include "cvector.hpp"

namespace img
{
    cvector<cvector<int>> filter(cvector<cvector<int>> img, cvector<cvector<int>> mask);
}

#endif
