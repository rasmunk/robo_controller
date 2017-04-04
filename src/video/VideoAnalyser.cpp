//
// Created by 40161642 on 15/12/2016.
//

#include <include/video/VideoAnalyser.h>
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;

// Prepare the video_writer
bool VideoAnalyser::initialise(const cv::Size& frame_size) {
    auto result = true;
    int codec = CV_FOURCC('M','J','P','G');
    double fps = 20.0;
    string video_name = "new_camera_test_2.avi";
    //bool isColor = (frame.type() == CV_8UC3);
    _video_writer.open(video_name, codec, fps, frame_size, true);
    // check whether the writer initialized correctly
    if (!_video_writer.isOpened()) {
        cerr << "Couldn't open the video writer" << "\n";
        result = false;
    }
    return result;
}

// Launches the current state of the object instance in a new thread and executes the analyse function
void VideoAnalyser::start() {
    cout << "Starting Analyser" << "\n";
    _runner = thread(&VideoAnalyser::analyse, this);
}

void VideoAnalyser::stop() {
    (*_keep_running).clear();
    cout << "Finished Analysing" << "\n";
}

void VideoAnalyser::quit()
{
    this->stop();
    if (_runner.joinable())
    {
        _runner.join();
    }
}

void VideoAnalyser::analyse() {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // 1 frame since last call
    double time_analysing = 0.0;

    bool found = false;
    // Retrieve a matrix from the shared structure
    int i = 0;
    while ((*_keep_running).test_and_set())
    {
        size_t size = _shared_frames->size();
        //cout << "size: " << size << "\n";
        if (size > 0)
        {
            start = std::chrono::high_resolution_clock::now();
            cv::Mat mat = _shared_frames->pop();
            cv::Mat flipped_mat;
            // Flip around x and y axis
            cv::flip(mat, flipped_mat, -1);
            //_video_writer.write(flipped_mat);
            found = _shared_detector->find(flipped_mat);
            end = std::chrono::high_resolution_clock::now();
            finish = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            if (finish > 0)
            {
                time_analysing = 1000 / finish;
                cout << "Time to analyze: " << time_analysing << "\n";
            }
        }
        ++i;
    }
}