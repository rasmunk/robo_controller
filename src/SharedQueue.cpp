//
// Created by 40161642 on 14/12/2016.
//
#include <include/SharedQueue.h>
using namespace cv;
using namespace std;

void SharedQueue::add(Mat&& mat)
{
    lock_guard<mutex> lock(_mutex);
    _queue.push(mat);
}

size_t SharedQueue::size() { return _queue.size(); }

// Retrieve the first item.
Mat SharedQueue::pop()
{
    lock_guard<mutex> lock(_mutex);
    Mat mat;
    if (_queue.size() > 0) {
        mat = _queue.front();
        _queue.pop();
    }
    return mat;
}