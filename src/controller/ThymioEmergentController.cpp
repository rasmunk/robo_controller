//
// Created by Rasmus Munk on 18/06/2017.
//

#include <include/controller/ThymioEmergentController.h>
#include <include/util/ea/Gene.h>
#include <include/robot/Thymio.h>

//TODO -> load weights lower and upper bounds from config
using namespace std;
using namespace std::placeholders;

ThymioEmergentController::ThymioEmergentController() {
    _emergent_configuration = make_unique<EmergentRobotConfiguration>(8, 0, 2);
    _emergent_configuration->initialize();
    _emergent_configuration->update();

    _thymio_interface->loadScript("BasicThymio.aesl");
    _thymio_interface->connectEvent("ObstacleDetected", bind(&ThymioEmergentController::callback_nn_translate, this, _1));
}

// TODO -> change assert to Expect
// Translates the incoming proximity values into motor speeds
void ThymioEmergentController::callback_nn_translate(const Values& proximity_values) {
    cout << "Obstacle: " << Aseba::DBusInterface::toString(proximity_values) << endl;
    // translate into input
    // range of proximity sensors -> normalized between 0.0 and 1.0
    vector<double> input;
    for (const auto &prox_value : proximity_values) {
        double norm_value = (double)(prox_value - Thymio::min_proximity) / (double)(Thymio::max_proximity - Thymio::min_proximity);
        input.push_back(norm_value);
    }
    vector<double> output = _emergent_configuration->get_activations(input);
    // TODO -> Test for this.
    qint16 new_left_speed = (qint16)(Thymio::max_speed * output.at(0));
    qint16 new_right_speed = (qint16)(Thymio::max_speed * output.at(0));
    cout << "New Speed, left: " << new_left_speed << " right: " << new_right_speed << endl;

    _thymio_interface->sendEventName("Speed", Values({new_left_speed, new_right_speed}));
}