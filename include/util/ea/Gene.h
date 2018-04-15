//
// Created by Rasmus Munk on 18/06/2017.
//

#ifndef EMERGENT_CONTROLLER_GENE_H
#define EMERGENT_CONTROLLER_GENE_H

#include <chrono>
#include <random>
#include <vector>

class Gene {
private:
    std::vector<bool> _encoding;
    double _value;
    std::default_random_engine _generator;
    std::uniform_int_distribution<> _dist_int;
    std::uniform_real_distribution<> _dist_real;

public:
    Gene();
    void mutate();
    double get_value();
};

#endif // EMERGENT_CONTROLLER_GENE_H
