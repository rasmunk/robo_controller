//
// Created by Rasmus Munk on 27/01/2017.
//

// Relies on the provided Aseba medulla DBUS interface library which was generated from https://github.com/aseba-community/aseba/tree/master/examples/clients/cpp-qt-dbus

#include <iostream>
#include <include/controller/ThymioController.h>
#include <QtDBus/QtDBus>
#include "../../include/controller/RobotControllerFactory.h"
#include "../../include/controller/ThymioController.h"

using namespace std;
using namespace std::placeholders;

// Copies the current state of the object instance in a new thread and executes the flocking function
void ThymioController::start()
{
    cout << "Started Flocking" << "\n";
    _runner = thread(&ThymioController::flocking, this);
}

void ThymioController::stop()
{
    (*_keep_running).clear();
    cout << "Flocking finsihed" << "\n";

}

void ThymioController::quit()
{
    this->stop();
    if (_runner.joinable())
    {
        _runner.join();
    }
}

void ThymioController::flocking()
{
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
}

void ThymioController::callback_avoid(const Values& event_values)
{
    // If detected -> average location, seperation and alignment
    cout << "Thymio encountered an obstacle: " << Aseba::DBusInterface::toString(event_values) << endl;
    _thymio_interface->sendEventName("Rotate", Values({}));
}

// Robot sees nothing -> sends it current speed on both motors
// if they are normal values -> do nothing -> else reset to normal -> forward
void ThymioController::callback_clear(const Values& event_values)
{
    cout << "Thymio sees nothing: " << Aseba::DBusInterface::toString(event_values) << endl;
    qint16 current_left_speed = event_values[0];
    qint16 current_right_speed = event_values[1];
    if (current_left_speed != normal_speed or current_right_speed != normal_speed)
    {
        cout << "Firing reset speed" << "\n";
        _thymio_interface->sendEventName("MoveNormally", Values({}));
    }
}


void ThymioController::callback_falling(const Values& event_values)
{
    cout << "Falling: " << Aseba::DBusInterface::toString(event_values) << endl;
    qint16 min_prox_distance = 2000;
    for (size_t i = 0; i < event_values.size(); ++i)
    {
        if (event_values[i] < min_prox_distance)
        {
            min_prox_distance = event_values[i];
        }
    }

    // If less than 800 for this particular sensor it's a good indicator that the surface is reflective.
    // e.g. a table of white paper
    // black carpet = 70
    if (min_prox_distance < 40)
    {
        _thymio_interface->sendEventName("Rotate", Values({}));
    }
}

// Robot sees nothing -> sends it current speed on both motors
// if they are normal values -> do nothing -> else reset to normal -> forward
void ThymioController::callback_keepalive(const Values& event_values)
{
    _thymio_interface->sendEventName("KeepAlive", Values({}));
}

void ThymioController::set_shared_detector(shared_ptr<Detector> shared_detector)
{
    _shared_detector = shared_detector;
}