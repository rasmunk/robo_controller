//
// Created by Rasmus Munk on 18/06/2017.
//
#include <include/controller/ThymioOAController.h>

using namespace std;
using namespace std::placeholders;
void ThymioOAController::start() {
    _runner = thread(&ThymioOAController::obstacle_avoidance, this);
}

void ThymioOAController::obstacle_avoidance() {
    cout << "Starting Obstacle Avoidance" << endl;
    // Instantiate state after state has been copied by the thread function
    char** argv;
    int argc;
    _core_application = make_unique<QCoreApplication>(argc,argv);
    _thymio_interface = make_unique<Aseba::DBusInterface>();
    cout << "Loading Aesl Script onto the robot" << "\n";
    _thymio_interface->loadScript("/etc/emergent_robot/ScriptDBusThymio.aesl");
    cout << "Configuring normalspeed and connect events" << "\n";
    _thymio_interface->setVariable("thymio-II", "normal_speed", Values({normal_speed}));
    _thymio_interface->sendEventName("MoveNormally", Values({})); // Sets the robots speed to normal_speed
    _thymio_interface->connectEvent("ObstacleDetected", bind(&ThymioController::callback_avoid, this, _1));
    _thymio_interface->connectEvent("Falling", bind(&ThymioController::callback_falling, this, _1));
    _thymio_interface->connectEvent("Clear", bind(&ThymioController::callback_clear, this, _1));
    _thymio_interface->connectEvent("Stop", bind(&ThymioController::callback_keepalive, this, _1));

    while((*_keep_running).test_and_set())
    {
        //cout << "Running" << "\n";
        // Wait for new events -> process them when they are registered
        _core_application->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::EventLoopExec);
    }
    cout << "Stopping the thymio" << "\n";
    _thymio_interface->sendEventName("Stop", Values({}));
    cout << "Finished Obstacle avoidance" << endl;
}