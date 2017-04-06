#include <opencv2/opencv.hpp>
#include <include/video/VideoAnalyser.h>
#include <include/detector/DetectorFactory.h>
#include <include/SharedFrame.h>
#include <include/video/VideoHandler.h>
#include <include/controller/RobotControllerFactory.h>


using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    // Launch the shared frame structure and the Detector factory
    DetectorFactory dec_factory;
    RobotControllerFactory robot_controller_factory;
    shared_ptr<FrameStructure> shared_frame = make_shared<SharedFrame>();
    auto shared_detector = shared_ptr<Detector>(move(dec_factory.make_detector(Robot)));
    shared_detector->initialize("emergent_controller/res/images/object.jpg");
    // Controller is spawned off into it's own thread
    auto robot_controller = robot_controller_factory.make_shared_robot_controller(Thymio);
    robot_controller->set_shared_detector(shared_detector);

    // move a new detector to the videoanalyser and take copy of the shared structure
    auto video_handler = VideoHandler{shared_frame};
    auto video_analyser = VideoAnalyser{shared_detector, shared_frame, video_handler.get_frame_size()};
    // Launches a thread that retrieves images from the camera and puts them into the shared structure
    video_handler.start();
    // Launches a thread that continously pulls images from the shared structure and tries to detect an entity within the image
    video_analyser.start();
    // Launches a thread that controls how the robot operates
    robot_controller->start();

    this_thread::sleep_for(300s);
    robot_controller->stop(); // Stops the execution and joins the thread
    video_analyser.stop();
    video_handler.stop();
    cout << "Main Finished" << "\n";
    return 0;
}