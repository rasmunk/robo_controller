/**
 * @file
 * @author Leo Cazenille <leo.cazenille@upmc.fr>
 *
 *
 */

#ifndef NEURALNETWORKEXCEPTION_H
#define NEURALNETWORKEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

namespace Neural {

/**
 * Exception class thrown what something bad happens
 * @author Leo Cazenille <leo.cazenille@upmc.fr>
 */
class NeuralNetworkException : public std::runtime_error {
public:
    NeuralNetworkException(const std::string& what_arg);
};

} // namespace Neural

#endif
