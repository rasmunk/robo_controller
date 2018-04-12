//
// Created by 40161642 on 15/12/2016.
//

#ifndef TEST3_VIDEOANALYSER_H
#define TEST3_VIDEOANALYSER_H
#include <atomic>
#include <include/FrameStructure.h>
#include <include/detector/Detector.h>
#include <memory>
#include <thread>

class VideoAnalyser {
private:
    std::shared_ptr<Detector> _shared_detector;
    std::shared_ptr<FrameStructure> _shared_frames;
    cv::VideoWriter _video_writer;
    std::thread _runner;
    std::unique_ptr<std::atomic_flag> _keep_running = std::make_unique<std::atomic_flag>(true);
    void analyse();
    void quit();
    bool initialise(const cv::Size&);

public:
    VideoAnalyser(VideoAnalyser&&) = default; // request automatic generated move constructor ->
        // http://stackoverflow.com/questions/16192865/providing-an-empty-user-defined-destructor-causes-compilation-error
    VideoAnalyser(std::shared_ptr<Detector> shared_detector,
        std::shared_ptr<FrameStructure> shared_frames,
        const cv::Size& frame_size)
        : _shared_detector(shared_detector)
        , _shared_frames(shared_frames)
    {
        initialise(frame_size);
    };
    ~VideoAnalyser() { this->quit(); };
    void start();
    void stop();
};

#endif // TEST3_VIDEOANALYSER_H
