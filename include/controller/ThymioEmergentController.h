//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H
#define EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H

#include <include/controller/ThymioController.h>
#include <include/util/neuralnetworks/MLP.h>

class ThymioEmergentController : public ThymioController {
private:
    std::unique_ptr<Neural::MLP> _mlp;
    unsigned int _num_inputs;
    unsigned int _num_hidden;
    unsigned int _num_outputs;
    bool _active_bias;

public:
    ThymioEmergentController(unsigned int num_inputs, unsigned int num_hidden, unsigned int num_outputs, bool active_bias = true) : _num_inputs(num_inputs), _num_hidden(num_hidden), _num_outputs(num_outputs), _active_bias(active_bias) {};
    void train_behavior();
    void start() override;
    void stop() override;

};


#endif //EMERGENT_CONTROLLER_THYMIOEMERGENTCONTROLLER_H
