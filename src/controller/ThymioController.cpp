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

void ThymioController::start() {
    cout << "Thymio Start" << endl;

}

void ThymioController::stop()
{
    (*_keep_running).clear();
}

void ThymioController::quit()
{
    this->stop();
    if (_runner.joinable())
    {
        _runner.join();
    }
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