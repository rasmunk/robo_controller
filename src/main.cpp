#include <include/SharedFrame.h>
#include <include/configuration/RobotConfiguration.h>
#include <include/controller/RobotControllerFactory.h>
#include <include/detector/DetectorFactory.h>
#include <include/manager/RobotManager.h>
#include <include/network/RobotServiceClient.h>
#include <include/network/GrpcServer.h>
#include <include/network/SimulationServiceImpl.h>
#include <include/video/VideoAnalyser.h>
#include <include/video/VideoHandler.h>
#include <include/network/RobotServiceImpl.h>
#include <future>

using namespace cv;
using namespace std;

enum Managed_by {NETWORK, LOCAL};
enum Connection_type {SIMULATION, PHYSICAL};

int main(int argc, char** argv)
{
    auto managed_by = Managed_by::NETWORK;
    auto connection_type = Connection_type::SIMULATION;
    Controller_type controller_type = ThymioObstacleAvoidance;
    vector<shared_ptr<RobotController>> controllers;

    int num_robots = 1;
    int base_port = 33333;
    RobotControllerFactory robot_controller_factory;
    for (int i = 0; i < num_robots; ++i) {
        RobotConfig robot_config;
        robot_config.set("ip", "127.0.0.1");
        robot_config.set("port", to_string(base_port));
        robot_config.set("aesl_file", "../res/config/OAThymio.aesl");
        base_port++;
        controllers.emplace_back(robot_controller_factory.make_shared_robot_controller(controller_type,
                                                                                      robot_config));
    }

    // Startup
    auto robo_manager = make_shared<RobotManager>();
    unique_ptr<RobotServiceClient> robot_service_client;
    if (connection_type == SIMULATION) {
        // Connect to simulator
        robot_service_client = make_unique<RobotServiceClient>("127.0.0.1:29000");
    }

    for (const auto& controller : controllers) {
        if (connection_type == SIMULATION) {
            // Spawn controller in simulator
            robo_manager->spawn_controller(*controller, controller_type,
                                           *robot_service_client);
        }
        robo_manager->run_controller(controller, controller_type);
    }

    // Network enabled
    unique_ptr<GrpcServer> robotserver;
    unique_ptr<RobotServiceImpl> service;
    if (managed_by == NETWORK && connection_type == SIMULATION) {
        // sink simulation client into the robot services
        service = make_unique<RobotServiceImpl>(robo_manager, move(robot_service_client));
        // Listen for robotservice messages to pass on
        robotserver = make_unique<GrpcServer>("127.0.0.1:30000", *service);
    }

    // keep on running for now
    promise<void>().get_future().wait();

    /*
    DetectorFactory dec_factory;
    auto shared_detector =
    shared_ptr<Detector>(move(dec_factory.make_detector(Robot)));
    shared_detector->initialize("emergent_controller/res/images/object.jpg");
    robot_controller->set_shared_detector(shared_detector);

    shared_ptr<FrameStructure> shared_frame = make_shared<SharedFrame>();
    auto video_handler = VideoHandler{shared_frame};
    // move a new detector to the videoanalyser and take copy of the shared
    structure auto video_analyser = VideoAnalyser{shared_detector, shared_frame,
    video_handler.get_frame_size()};

    // Launches a thread that retrieves images from the camera and puts them into
    the shared structure video_handler.start();
    // Launches a thread that continously pulls images from the shared structure
    and tries to detect an entity within the image video_analyser.start();

        // Launches a thread that controls how the robot operates
    robot_controller->start();

    this_thread::sleep_for(300s);
    robot_controller->stop(); // Stops the execution and joins the thread
    video_analyser.stop();
    video_handler.stop();
    */
    return 0;
}