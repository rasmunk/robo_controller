//
// Created by Rasmus Munk on 22/08/2017.
//

#ifndef EMERGENT_CONTROLLER_ASEBAROBOTCONFIGURATION_H
#define EMERGENT_CONTROLLER_ASEBAROBOTCONFIGURATION_H

/*
 * Defines the configuraiton properties of an underlyging aseba controlled robot
 *
 */

#include <include/controller/RobotController.h>

class AsebaRobotConfiguration : public RobotConfiguration {
public:
    void initialize() override;

private:
};

#endif // EMERGENT_CONTROLLER_ASEBAROBOTCONFIGURATION_H
