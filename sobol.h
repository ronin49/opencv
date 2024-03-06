#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
void sobol(Mat src, Mat &dst, Mat kernel=
    (Mat_<double>(3,3) << 1, 0, -1, 2, 0, -2, 1, 0, -1))
{
    int rows = src.rows, cols = src.cols;
    dst = Mat(rows, cols, src.type());
    // Taking care of edge values
    // Make border = kernel.rows / 2;
    int sz = kernel.rows / 2;
    copyMakeBorder(src, src, sz, sz, sz, sz, BORDER_REPLICATE);
    for (int i = 0; i < rows; i++)
    {
        uchar *dptr = dst.ptr(i);
        for (int j = 0; j < cols; j++)
        {
            double value = 0;
            for (int k = -sz; k <= sz; k++)
            {
                // slightly faster results when we create a ptr due to more efficient memory access.
                uchar *sptr = src.ptr(i + sz + k);
                for (int l = -sz; l <= sz; l++)
                {
                    value += kernel.ptr<double>(k + sz)[l + sz] * sptr[j + sz + l];
                }
            }
            dptr[j] = saturate_cast<uchar>(value);
        }
    }
}
