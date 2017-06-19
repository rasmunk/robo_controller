//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
#define EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H

#include <include/controller/ThymioController.h>

class ThymioOAController : public ThymioController {
private:
    void obstacle_avoidance();
public:
    void start() override;
};

#endif //EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
