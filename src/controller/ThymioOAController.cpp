//
// Created by Rasmus Munk on 18/06/2017.
//

#include <random>
#include <include/controller/ThymioOAController.h>
#include <include/robot/Thymio.h>

using namespace std;
using namespace std::placeholders;

ThymioOAController::ThymioOAController() : ThymioController() {}


void ThymioOAController::setup() {
    _actions["ObstacleDetected"] = std::bind(&ThymioOAController::obstacle_detected, this);
    _actions["SeeNothing"] = std::bind(&ThymioOAController::see_nothing, this);
    _actions["Falling"] = std::bind(&ThymioOAController::falling, this);
    _aseba_interface->sendEvent("Forward");
}

void ThymioOAController::obstacle_detected() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> real_dis(0.1, 1.0);
    std::uniform_int_distribution<> int_dis(1000, 2000);

    _aseba_interface->sendEvent("Reverse");
    QThread::msleep(2000);
    if (real_dis(gen) < 0.5) {
        _aseba_interface->sendEvent("RotateLeft");
    } else {
        _aseba_interface->sendEvent("RotateRight");
    }
    // sleep between 0 and 5 seconds

    QThread::msleep((unsigned long) int_dis(gen));
    _aseba_interface->sendEvent("Forward");
}

void ThymioOAController::see_nothing() {
    _aseba_interface->sendEvent("Forward");
}

// TODO -> implement
void ThymioOAController::falling()
{

}