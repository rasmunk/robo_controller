//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
#define EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H

#include <include/controller/ThymioController.h>

class ThymioOAController : public ThymioController {
public:
    ThymioOAController(const RobotConfig&);

    void setup() override;

private:
    void obstacle_detected();

    void see_nothing();

    void falling();
};

#endif // EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
