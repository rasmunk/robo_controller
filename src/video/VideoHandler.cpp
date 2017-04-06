//
// Created by 40161642 on 14/12/2016.
//

#include <include/video/VideoHandler.h>
using namespace cv;
using namespace std;

VideoHandler::VideoHandler(unique_ptr<FrameStructure> structure) : _structure(move(structure))
{
    if (!initialise())
    {
        exit(-1);
    }
}

VideoHandler::VideoHandler(shared_ptr<FrameStructure> shared_structure) : _shared_structure(shared_structure)
{
    if (!initialise())
    {
        exit(-1);
    }
}




bool VideoHandler::initialise()
{
    auto result = true;
    // setup capture
    Mat frame;
    cout << "Initializing the camera" << "\n";
    _video_cap.open(0);
    if(!_video_cap.isOpened())
    {
        cerr << "Couldn't open the video capture" << "\n";
        result = false;
    } else {
        _video_cap >> frame; // Retreive a single frame from the camera;
        _frame_size = frame.size();
    }
    if (frame.empty())
    {
        cerr << "A blank frame was returned from the camera" << "\n";
        result = false;
    }
    cout << "Camera Initialized" << "\n";
    // setup writer
   /* int codec = CV_FOURCC('M','J','P','G');
    double fps = 25.0;
    string video_name = "camera_test.avi";
    bool isColor = (frame.type() == CV_8UC3);
    _video_writer.open(video_name, codec, fps, frame.size(), isColor);
    // check whether the writer initialized correctly
    if (!_video_writer.isOpened()) {
       cerr << "Couldn't open the video writer" << "\n";
        result = false;
    }*/
    return result;
}

void VideoHandler::capture()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    double fps = 0.0;

    while ((*_keep_running).test_and_set())
    {
        start = std::chrono::high_resolution_clock::now();
        // redeclare new frame
        Mat frame;
        // Read the next frame into the Mat
        if (!_video_cap.read(frame))
        {
            cerr << "A blank frame was returned from the camera";
            break;
        }
        end = std::chrono::high_resolution_clock::now();
        finish = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (finish > 0)
        {
            fps = 1000 / finish;
            //cout << "Capture fps: " << fps << "\n";
        }
        _shared_structure->add(move(frame));
    }
}


// launches a thread that keeps adding frames into the FrameStructure
void VideoHandler::start()
{
    cout << "Started recording" << "\n";
    _runner = std::thread(&VideoHandler::capture, this);
}

// kills the thread that record frames into the FrameStructure
void VideoHandler::stop()
{
    (*_keep_running).clear();
    cout << "Finished recording" << "\n";
}

void VideoHandler::quit()
{
    this->stop();
    if (_runner.joinable())
    {
        _runner.join();
    }
}

cv::Size VideoHandler::get_frame_size() {
    return _frame_size;
}

