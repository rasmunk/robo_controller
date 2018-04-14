//
// Created by Rasmus Munk on 27/08/2017.
//

#include <include/configuration/EmergentRobotConfiguration.h>

using namespace std;

EmergentRobotConfiguration::EmergentRobotConfiguration(
    unsigned int num_inputs, unsigned int num_hidden, unsigned int num_outputs, bool active_bias)
{
    vector<unsigned int> hidden_layer;
    vector<double> weights;
    _num_inputs = num_inputs;
    _num_hidden = num_hidden;
    _num_outputs = num_outputs;
    _active_bias = active_bias;
    _genome = make_unique<network::Genome>();
    hidden_layer.push_back(_num_hidden);
/*    for (int i = 0; i < _genome->nn_weights_size(); ++i) {
        weights.push_back(_genome->nn_weights(i));
    }
    _mlp = make_unique<Neural::MLP>(
        weights, _num_inputs, _num_outputs, hidden_layer, _active_bias, true);*/
}

void EmergentRobotConfiguration::initialize() {}

void EmergentRobotConfiguration::update() {}

const vector<double>& EmergentRobotConfiguration::get_activations(vector<double>& input) const
{
    _mlp->setInputs(input);
    _mlp->step();
    return _mlp->readOut();
}