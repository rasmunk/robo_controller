//
// Created by Rasmus Munk on 18/06/2017.
//
#include <include/controller/ThymioOAController.h>
#include <include/robot/Thymio.h>

using namespace std;
using namespace std::placeholders;

ThymioOAController::ThymioOAController() {
    _thymio_interface->loadScript("BasicThymio.aesl");
    /*_thymio_interface->connectEvent("Stop", bind(&ThymioController::callback_keepalive, this, _1));
    _thymio_interface->connectEvent("SeeNothing", bind(&ThymioOAController::callback_clear, this, _1));
    _thymio_interface->connectEvent("ObstacleDetected", bind(&ThymioOAController::callback_avoid, this, _1));
    */

    _thymio_interface->sendEventName("SetSpeed", Values({Thymio::normal_speed}));
    _thymio_interface->sendEventName("Move", Values({}));
}

void ThymioOAController::callback_avoid(const Values& event_values)
{
    // If detected -> average location, seperation and alignment
    cout << "Thymio encountered an obstacle: " << Aseba::DBusInterface::toString(event_values) << endl;
    _thymio_interface->sendEventName("Rotate", Values({}));
}

// Robot sees nothing -> sends it current speed on both motors
// if they are normal val*ues -> do nothing -> else reset to normal -> forward
void ThymioOAController::callback_clear(const Values& event_values)
{
    cout << "Thymio sees nothing: " << Aseba::DBusInterface::toString(event_values) << endl;
    qint16 current_left_speed = event_values[0];
    qint16 current_right_speed = event_values[1];
    if (current_left_speed != Thymio::normal_speed or current_right_speed != Thymio::normal_speed)
    {
        cout << "Firing reset speed" << "\n";
        _thymio_interface->sendEventName("MoveNormally", Values({}));
    }
}

void ThymioOAController::callback_falling(const Values& event_values)
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