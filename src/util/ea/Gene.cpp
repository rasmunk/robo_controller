//
// Created by Rasmus Munk on 18/06/2017.
//
#include <include/util/ea/Gene.h>

using namespace std;
Gene::Gene()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    _generator = std::default_random_engine(seed);
    _dist_int = std::uniform_int_distribution<>(0, 1);
    _encoding.resize(8);
    for (int i = 0; i < _encoding.size(); ++i) {
        _encoding[i] = (_dist_int(_generator));
    }
    _dist_real = std::uniform_real_distribution<>(0.0, 1.0);
}

void Gene::mutate()
{
    for (int i = 0; i < _encoding.size(); ++i) {
        if (_dist_real(_generator) < 0.1) {
            if (_encoding[i]) {
                _encoding[i] = false;
            } else {
                _encoding[i] = true;
            }
        }
    }
}

double Gene::get_value()
{
    _value = 0.0;
    for (int i = 0; i < _encoding.size(); ++i) {
        if (_encoding[i]) {
            _value += pow(2, i);
        }
    }
    return _value;
}