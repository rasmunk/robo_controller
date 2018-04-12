//
// Created by Rasmus Munk on 04/02/2017.
//

#include <include/SharedFrame.h>

using namespace cv;
using namespace std;

void SharedFrame::add(cv::Mat&& mat)
{
    lock_guard<mutex> lock(_mutex);
    _mat = mat;
}

// clones the internal Mat to return in, afterwards the local copy is destroyed
Mat SharedFrame::pop()
{
    lock_guard<mutex> lock(_mutex);
    Mat mat = _mat.clone();
    _mat.release();
    return mat;
}

size_t SharedFrame::size() { return _mat.total(); }