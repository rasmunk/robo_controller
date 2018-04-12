//
// Created by Rasmus Munk on 22/08/2017.
//

#ifndef EMERGENT_CONTROLLER_EMERGENTROBOTCONFIGURATION_H
#define EMERGENT_CONTROLLER_EMERGENTROBOTCONFIGURATION_H

#include <include/configuration/RobotConfiguration.h>
#include <include/util/neuralnetworks/MLP.h>
#include <simulation.grpc.pb.h>

/*
 * Defines the configuration of how an evolving robot controller is configured.
 * E.g. it's NN composition
 */

class EmergentRobotConfiguration : public RobotConfiguration {
public:
    EmergentRobotConfiguration() {}
    EmergentRobotConfiguration(unsigned int num_inputs, unsigned int num_hidden,
        unsigned int num_outputs, bool active_bias = true);
    void initialize() override;
    void update() override;
    const std::vector<double>& get_activations(std::vector<double>&) const;

private:
    std::unique_ptr<network::Genome> _genome;
    std::unique_ptr<Neural::MLP> _mlp;
    unsigned int _num_inputs;
    unsigned int _num_hidden;
    unsigned int _num_outputs;
    bool _active_bias;
};

#endif // EMERGENT_CONTROLLER_EMERGENTROBOTCONFIGURATION_H
