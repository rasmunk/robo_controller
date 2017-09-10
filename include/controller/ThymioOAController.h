//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
#define EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H

#include <include/controller/ThymioController.h>

class ThymioOAController : public ThymioController {
public:
    ThymioOAController();
    void callback_avoid(const Values& event_values); // Callback function for the thymio -> has seen an obstacle
    void callback_clear(const Values& event_values); // sees nothing -> passes the current speed
    void callback_falling(const Values& event_values); // about to fall
};

#endif //EMERGENT_CONTROLLER_THYMIOOACONTROLLER_H
