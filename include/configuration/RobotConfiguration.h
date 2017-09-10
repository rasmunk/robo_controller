//
// Created by Rasmus Munk on 22/08/2017.
//

#ifndef EMERGENT_CONTROLLER_ROBOTCONFIGURATION_H
#define EMERGENT_CONTROLLER_ROBOTCONFIGURATION_H

class RobotConfiguration {
public:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual ~RobotConfiguration() = default;
};

#endif //EMERGENT_CONTROLLER_ROBOTCONFIGURATION_H
