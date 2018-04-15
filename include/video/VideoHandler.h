//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_VIDEOHANDLER_H
#define TEST3_VIDEOHANDLER_H

#include <atomic>
#include <include/FrameStructure.h>
#include <opencv2/opencv.hpp>
#include <thread>

class VideoHandler {
private:
    std::unique_ptr<FrameStructure> _structure;
    std::shared_ptr<FrameStructure> _shared_structure;
    cv::VideoCapture _video_cap;
    cv::Size _frame_size;
    std::thread _runner;
    std::unique_ptr<std::atomic_flag> _keep_running = std::make_unique<std::atomic_flag>(true);
    void capture();
    bool initialise();
    void quit();

public:
    VideoHandler(VideoHandler&&)
        = default; // request automatic generated move constructor ->
                   // http://stackoverflow.com/questions/16192865/providing-an-empty-user-defined-destructor-causes-compilation-error
    VideoHandler(std::unique_ptr<FrameStructure> structure);
    VideoHandler(std::shared_ptr<FrameStructure> shared_structure);
    ~VideoHandler() { this->quit(); };
    void start();
    void stop();
    cv::Size get_frame_size();
};

#endif // TEST3_VIDEOHANDLER_H
