//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H
#define EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H

#include <include/controller/ThymioController.h>

#include <cmake-build-debug/proto-src/simulation.pb.h>
#include <include/configuration/EmergentRobotConfiguration.h>

class ThymioEmergentController : public ThymioController {
private:
    std::unique_ptr<EmergentRobotConfiguration> _emergent_configuration;
    void callback_nn_translate(const Values&);
public:
    ThymioEmergentController();
};

#endif //EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H
