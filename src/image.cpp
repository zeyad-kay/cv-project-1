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
}