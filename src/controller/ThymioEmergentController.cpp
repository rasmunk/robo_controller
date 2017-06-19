//
// Created by Rasmus Munk on 18/06/2017.
//

#include <include/controller/ThymioEmergentController.h>
#include <include/util/ea/Gene.h>

//TODO -> load weights lower and upper bounds from config
using namespace std;
void ThymioEmergentController::start() {
    train_behavior();
    //_runner = thread(&ThymioEmergentController::train_behavior, this);
}

void ThymioEmergentController::train_behavior() {
    vector<double> weights;
    vector<unsigned int> hidden_layer;
    hidden_layer.push_back(_num_hidden);
    vector<Gene> encoded_weights((_num_inputs * _num_hidden) + (_num_hidden * _num_outputs));
    for (int i = 0; i < encoded_weights.size(); ++i) { weights.push_back(encoded_weights[i].get_value()); };
    _mlp = make_unique<Neural::MLP>(weights, _num_inputs, _num_outputs, hidden_layer, true, true);
}


void ThymioEmergentController::stop() {

}